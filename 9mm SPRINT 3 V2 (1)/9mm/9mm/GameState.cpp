#include <sstream>
#include "GameState.h"
#include "Config.h"
#include "GameOverW.h"
#include "GameOverB.h"
#include <iostream>
#include "Anchor.h"
#include <algorithm>

Anchor p0(0, sf::Vector2f(170, 70));
Anchor p1(1, sf::Vector2f(480, 70));
Anchor p2(2, sf::Vector2f(790, 70));

Anchor p3(3, sf::Vector2f(790, 380));
Anchor p4(4, sf::Vector2f(790, 690));

Anchor p5(5, sf::Vector2f(480, 690));
Anchor p6(6, sf::Vector2f(170, 690));
Anchor p7(7, sf::Vector2f(170, 380));

Anchor p8(8, sf::Vector2f(265, 380));
Anchor p9(9, sf::Vector2f(265, 170));
Anchor p10(10, sf::Vector2f(480, 170));
Anchor p11(11, sf::Vector2f(695, 170));
Anchor p12(12, sf::Vector2f(695, 380));
Anchor p13(13, sf::Vector2f(695, 590));
Anchor p14(14, sf::Vector2f(480, 590));
Anchor p15(15, sf::Vector2f(265, 590));

Anchor p16(16, sf::Vector2f(350, 380));
Anchor p17(17, sf::Vector2f(350, 250));
Anchor p18(18, sf::Vector2f(480, 250));
Anchor p19(19, sf::Vector2f(610, 250));
Anchor p20(20, sf::Vector2f(610, 380));
Anchor p21(21, sf::Vector2f(610, 510));
Anchor p22(22, sf::Vector2f(480, 510));
Anchor p23(23, sf::Vector2f(350, 510));

Anchor points[24] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9,
p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
p20, p21, p22, p23 };


int p1coin = 9;
int p2coin = 9;
int p1total = 9;
int p2total = 9;
int old_pos;

// Phases
bool select;
bool remove_phase = false;
bool fly_phase = false;
bool no_legal_moves = false;

bool L1 = false, L2 = false, L3 = false, L4 = false, L5 = false, L6 = false, L7 = false, L8 = false, 
L9 = false, L10 = false, L11 = false, L12 = false, L13 = false , L14 = false, L15 = false, L16 = false;

int test = 1;


GameState::GameState(GameDataRef data) :_data(data)
{

}

void GameState::Init() {

	gameState = STATE_PLAYING_PLAYER;
	turn = P1;

	this->_data->assets.LoadTexture("Background", GAME_BACKGROUND);
	this->_data->assets.LoadTexture("bstone", BLACK_PIECE_PATH);
	this->_data->assets.LoadTexture("wstone", WHITE_PIECE_PATH);
	this->_data->assets.LoadTexture("counterW", white9);
	this->_data->assets.LoadTexture("counterB", black9);

	background.setTexture(this->_data->assets.GetTexture("Background"));
	bstone.setTexture(this->_data->assets.GetTexture("bstone"));
	wstone.setTexture(this->_data->assets.GetTexture("wstone"));
	counterW.setTexture(this->_data->assets.GetTexture("counterW"));
	counterB.setTexture(this->_data->assets.GetTexture("counterB"));



	this->background.setPosition((SCREEN_WIDTH / 2) - (this->background.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->background.getGlobalBounds().height / 2));
	this->counterW.setPosition((SCREEN_WIDTH) - (this->counterW.getGlobalBounds().width * 3) , (SCREEN_HEIGHT / 2) - (this->counterW.getGlobalBounds().height / 2));
	this->counterB.setPosition((SCREEN_WIDTH / 2) - (this->counterB.getGlobalBounds().width * 10), (SCREEN_HEIGHT / 2) - (this->counterB.getGlobalBounds().height / 2));

	InitBoardPieces();

	for (int x = 0; x < 24; x++) {
		boardArray[x] = EMPTY_PIECE;
		}
	}


void GameState::HandleInput() {

	sf::Event event;

	while (this->_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->_data->window.close();
		}

		else if (fly_phase == true) {
				sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
				int x = CheckPos(touchPoint.x, touchPoint.y);

				if (this->_data->input.isSpriteClicked(this->background, sf::Mouse::Left, this->_data->window)) {

					if (remove_phase == true) {
						this->CheckAndDelete(x);
					}

					if (select == false) {
						if (remove_phase == false) {

							this->SelectCoin(x);
						}
					}

					if (select == true) {
						if (remove_phase == false) {

							this->MoveCoin(x);
						}

					}
				}
			}

		else if (this->_data->input.isSpriteClicked(this->background, sf::Mouse::Left, this->_data->window)){
				sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
				int x = CheckPos(touchPoint.x, touchPoint.y);

			if (fly_phase == false) {

				if (remove_phase == false) {

					this->CheckAndPlace(x);
				}

				if (remove_phase == true) {

					this->CheckAndDelete(x);
				}
			}
		}
	}
}

void GameState::Update(float dt)
{

}

void GameState::Draw(float dt)
{

	this->_data->window.clear(sf::Color::White);
	this->_data->window.draw(this->background);
	this->_data->window.draw(this->counterW);

	this->_data->window.draw(this->counterB);

	for (int x = 0; x < 24; x++) {
		this->_data->window.draw(this->boardPieces[x]);
	}
	this->_data->window.display();
}

void GameState::DecerementImageB(sf::Sprite x, int y) {

	if (y == 8) {
		this->_data->assets.LoadTexture("counterB", black8);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 7) {
		this->_data->assets.LoadTexture("counterB", black7);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 6) {
		this->_data->assets.LoadTexture("counterB", black6);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 5) {
		this->_data->assets.LoadTexture("counterB", black5);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 4) {
		this->_data->assets.LoadTexture("counterB", black4);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 3) {
		this->_data->assets.LoadTexture("counterB", black3);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 2) {
		this->_data->assets.LoadTexture("counterB", black2);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 1) {
		this->_data->assets.LoadTexture("counterB", black1);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
	if (y == 0) {
		this->_data->assets.LoadTexture("counterB", black0);
		x.setTexture(this->_data->assets.GetTexture("counterB"));
	}
}

void GameState::DecerementImageW(sf::Sprite x, int y) {

	if (y == 8) {
		this->_data->assets.LoadTexture("counterW", white8);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 7) {
		this->_data->assets.LoadTexture("counterW", white7);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 6) {
		this->_data->assets.LoadTexture("counterW", white6);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 5) {
		this->_data->assets.LoadTexture("counterW", white5);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 4) {
		this->_data->assets.LoadTexture("counterW", white4);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 3) {
		this->_data->assets.LoadTexture("counterW", white3);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 2) {
		this->_data->assets.LoadTexture("counterW", white2);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 1) {
		this->_data->assets.LoadTexture("counterW", white1);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
	if (y == 0) {
		this->_data->assets.LoadTexture("counterW", white0);
		x.setTexture(this->_data->assets.GetTexture("counterW"));
	}
}

void GameState::InitBoardPieces() {
	for (int x = 0; x < 24; x++) {
		boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
		boardPieces[x].setPosition(points[x].getPositionX(), points[x].getPositionY());
		boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
	}
	for (int x = 0; x < 24; x++) {
		boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
		boardPieces[x].setPosition(points[x].getPositionX(), points[x].getPositionY());
		boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
	}
}

int GameState::CheckPos(int x, int y) {
	int pos;


	if (x < 205 && y < 105) {
		return pos = 0;
	}

	else if (x < 515 && x > 480 && y < 105) {
		return pos = 1;
		
	}

	else if (x > 790 && y < 105) {
		return pos = 2;
		
	}

	else if (x > 790 && y > 380 && y < 420) {
		return pos = 3;
		
	}

	else if (x > 790 && y > 685) {
		return pos = 4;
		
	}

	else if (x > 485 && x < 515 && y > 695) {
		return pos = 5;
		
	}

	else if (x < 205 && y > 680) {
		return pos = 6;
		
	}

	else if (x < 205 && y > 380 && y < 420) {
		return pos = 7;
		
	}

	else if (x > 265 && x < 300 && y > 383 && y < 415) {
		return pos = 8;
		
	}

	else if (x > 265 && x < 300 && y > 170 && y < 200) {
		return pos = 9;
		
	}

	else if (x < 515 && x > 480 && y > 170 && y < 200) {
		return pos = 10;
	}
	

	else if (x > 700 && x < 725 && y > 170 && y < 200) {
		return pos = 11;
		;
	}

	else if (x > 700 && x < 725 && y > 380 && y < 420) {
		return pos = 12;
		
	}

	else if (x > 700 && x < 725 && y > 590 && y < 635) {
		return pos = 13;
		
	}

	else if (x > 485 && x < 515 && y > 590 && y < 635) {
		return pos = 14;
		
	}

	else if (x > 265 && x < 300 && y > 590 && y < 635) {
		return pos = 15;
		
	}

	else if (x > 355 && x < 380 && y > 385 && y < 415) {
		return pos = 16;
		
	}

	else if (x > 355 && x < 380 && y > 255 && y < 285) {
		return pos = 17;
		
	}

	else if (x < 515 && x > 480 && y > 255 && y < 285) {
		return pos = 18;
		
	}

	else if (x > 610 && x < 649 && y > 255 && y < 285) {
		return pos = 19;
		
	}

	else if (x > 610 && x < 649 && y > 380 && y < 420) {
		return pos = 20;
		
	}

	else if (x > 610 && x < 649 && y > 510 && y < 545) {
		return pos = 21;
		
	}

	else if (x > 485 && x < 515 && y > 510 && y < 545) {
		return pos = 22;
		
	}

	else if (x > 355 && x < 380 && y > 510 && y < 545) {
		return pos = 23;
		
	}

	else {
		return EMPTY_PIECE;
	}

}

bool GameState::CheckMill(int board[]) {

	if (board[0] == BLACK_STONE || board[0] == BLACK_STONE_MILLED) {
		if (board[1] == BLACK_STONE || board[1] == BLACK_STONE_MILLED) {
			if (board[2] == BLACK_STONE || board[2] == BLACK_STONE_MILLED) {
				if (L1 == false) {

					std::cout << "MILL FORMED : LINE 1" << std::endl;;
					return L1 = true;
				}
			}
		}
	}

	if (board[0] == BLACK_STONE || board[0] == BLACK_STONE_MILLED) {
		if (board[7] == BLACK_STONE || board[7] == BLACK_STONE_MILLED) {
			if (board[6] == BLACK_STONE || board[6] == BLACK_STONE_MILLED) {
				if (L2 == false) {

					std::cout << "MILL FORMED : LINE 2" << std::endl;;;
					return L2 = true;
				}
			}
		}
	}

	if (board[2] == BLACK_STONE || board[2] == BLACK_STONE_MILLED) {
		if (board[3] == BLACK_STONE || board[3] == BLACK_STONE_MILLED) {
			if (board[4] == BLACK_STONE || board[4] == BLACK_STONE_MILLED) {
				if (L3 == false) {

					std::cout << "MILL FORMED : LINE 3" << std::endl;;;
					return L3 = true;
				}
			}
		}
	}

	if (board[4] == BLACK_STONE || board[4] == BLACK_STONE_MILLED) {
		if (board[5] == BLACK_STONE || board[5] == BLACK_STONE_MILLED) {
			if (board[6] == BLACK_STONE || board[6] == BLACK_STONE_MILLED) {
				if (L4 == false) {

					std::cout << "MILL FORMED : LINE 4" << std::endl;;;
					return L4 = true;
				}
			}
		}
	}

	if (board[15] == BLACK_STONE || board[15] == BLACK_STONE_MILLED) {
		if (board[8] == BLACK_STONE || board[8] == BLACK_STONE_MILLED) {
			if (board[9] == BLACK_STONE || board[9] == BLACK_STONE_MILLED) {
				if (L5 == false) {

					std::cout << "MILL FORMED : LINE 5" << std::endl;;;
					return L5 = true;
				}
			}
		}
	}

	if (board[9] == BLACK_STONE || board[9] == BLACK_STONE_MILLED) {
		if (board[10] == BLACK_STONE || board[10] == BLACK_STONE_MILLED) {
			if (board[11] == BLACK_STONE || board[11] == BLACK_STONE_MILLED) {
				if (L6 == false) {

					std::cout << "MILL FORMED : LINE 6" << std::endl;;;
					return L6 = true;
				}
			}
		}
	}

	if (board[11] == BLACK_STONE || board[11] == BLACK_STONE_MILLED) {
		if (board[12] == BLACK_STONE || board[12] == BLACK_STONE_MILLED) {
			if (board[13] == BLACK_STONE || board[13] == BLACK_STONE_MILLED) {
				if (L7 == false) {

					std::cout << "MILL FORMED : LINE 7" << std::endl;;;
					return L7 = true;
				}
			}
		}
	}


	if (board[13] == BLACK_STONE || board[13] == BLACK_STONE_MILLED) {
		if (board[14] == BLACK_STONE || board[14] == BLACK_STONE_MILLED) {
			if (board[15] == BLACK_STONE || board[15] == BLACK_STONE_MILLED) {
				if (L8 == false) {

					std::cout << "MILL FORMED : LINE 8" << std::endl;;;
					return L8 = true;
				}
			}
		}
	}

	if (board[23] == BLACK_STONE || board[23] == BLACK_STONE_MILLED) {
		if (board[16] == BLACK_STONE || board[16] == BLACK_STONE_MILLED) {
			if (board[17] == BLACK_STONE || board[17] == BLACK_STONE_MILLED) {
				if (L9 == false) {

					std::cout << "MILL FORMED : LINE 9" << std::endl;;;
					return L9 = true;
				}
			}
		}
	}

	if (board[17] == BLACK_STONE || board[17] == BLACK_STONE_MILLED) {
		if (board[18] == BLACK_STONE || board[18] == BLACK_STONE_MILLED) {
			if (board[19] == BLACK_STONE || board[19] == BLACK_STONE_MILLED) {
				if (L10 == false) {

					std::cout << "MILL FORMED : LINE 10" << std::endl;;;
					return L10 = true;
				}
			}
		}
	}

	if (board[19] == BLACK_STONE || board[19] == BLACK_STONE_MILLED) {
		if (board[20] == BLACK_STONE || board[20] == BLACK_STONE_MILLED) {
			if (board[21] == BLACK_STONE || board[21] == BLACK_STONE_MILLED) {
				if (L11 == false) {

					std::cout << "MILL FORMED : LINE 11" << std::endl;;;
					return L11 = true;
				}
			}
		}
	}

	if (board[21] == BLACK_STONE || board[21] == BLACK_STONE_MILLED) {
		if (board[22] == BLACK_STONE || board[22] == BLACK_STONE_MILLED) {
			if (board[23] == BLACK_STONE || board[23] == BLACK_STONE_MILLED) {
				if (L12 == false) {

					std::cout << "MILL FORMED : LINE 12" << std::endl;;;
					return L12 = true;
				}
			}
		}
	}

	if (board[7] == BLACK_STONE || board[7] == BLACK_STONE_MILLED) {
		if (board[8] == BLACK_STONE || board[8] == BLACK_STONE_MILLED) {
			if (board[16] == BLACK_STONE || board[16] == BLACK_STONE_MILLED) {
				if (L13 == false) {

					std::cout << "MILL FORMED : LINE 13" << std::endl;;;
					return L13 = true;
				}
			}
		}
	}

	if (board[1] == BLACK_STONE || board[1] == BLACK_STONE_MILLED) {
		if (board[10] == BLACK_STONE || board[10] == BLACK_STONE_MILLED) {
			if (board[18] == BLACK_STONE || board[18] == BLACK_STONE_MILLED) {
				if (L14 == false) {

					std::cout << "MILL FORMED : LINE 14" << std::endl;;;
					return L14 = true;
				}
			}
		}
	}

	if (board[3] == BLACK_STONE || board[3] == BLACK_STONE_MILLED) {
		if (board[12] == BLACK_STONE || board[12] == BLACK_STONE_MILLED) {
			if (board[20] == BLACK_STONE || board[20] == BLACK_STONE_MILLED) {
				if (L15 == false) {

					std::cout << "MILL FORMED : LINE 15" << std::endl;;;
					return L15 = true;
				}
			}
		}
	}

	if (board[5] == BLACK_STONE || board[5] == BLACK_STONE_MILLED) {
		if (board[14] == BLACK_STONE || board[14] == BLACK_STONE_MILLED) {
			if (board[22] == BLACK_STONE || board[22] == BLACK_STONE_MILLED) {
				if (L16 == false) {

					std::cout << "MILL FORMED : LINE 16" << std::endl;;;
					return L16 = true;
				}
			}
		}
	}


	if (board[0] == WHITE_STONE || board[0] == WHITE_STONE_MILLED) {
		if (board[1] == WHITE_STONE || board[1] == WHITE_STONE_MILLED) {
			if (board[2] == WHITE_STONE || board[2] == WHITE_STONE_MILLED) {
				if (L1 == false) {

					std::cout << "MILL FORMED : LINE 1" << std::endl;;;
					return L1 = true;
				}
			}
		}
	}

	if (board[0] == WHITE_STONE || board[0] == WHITE_STONE_MILLED) {
		if (board[7] == WHITE_STONE || board[7] == WHITE_STONE_MILLED) {
			if (board[6] == WHITE_STONE || board[6] == WHITE_STONE_MILLED) {
				if (L2 == false) {

					std::cout << "MILL FORMED : LINE 2" << std::endl;;;
					return L2 = true;
				}
			}
		}
	}

	if (board[2] == WHITE_STONE || board[2] == WHITE_STONE_MILLED) {
		if (board[3] == WHITE_STONE || board[3] == WHITE_STONE_MILLED) {
			if (board[4] == WHITE_STONE || board[4] == WHITE_STONE_MILLED) {
				if (L3 == false) {

					std::cout << "MILL FORMED : LINE 3" << std::endl;;;
					return L3 = true;
				}
			}
		}
	}

	if (board[4] == WHITE_STONE || board[4] == WHITE_STONE_MILLED) {
		if (board[5] == WHITE_STONE || board[5] == WHITE_STONE_MILLED) {
			if (board[6] == WHITE_STONE || board[6] == WHITE_STONE_MILLED) {
				if (L4 == false) {

					std::cout << "MILL FORMED : LINE 4" << std::endl;;;
					return L4 = true;
				}
			}
		}
	}

	if (board[15] == WHITE_STONE || board[15] == WHITE_STONE_MILLED) {
		if (board[8] == WHITE_STONE || board[8] == WHITE_STONE_MILLED) {
			if (board[9] == WHITE_STONE || board[9] == WHITE_STONE_MILLED) {
				if (L5 == false) {

					std::cout << "MILL FORMED : LINE 5" << std::endl;;;
					return L5 = true;
				}
			}
		}
	}

	if (board[9] == WHITE_STONE || board[9] == WHITE_STONE_MILLED) {
		if (board[10] == WHITE_STONE || board[10] == WHITE_STONE_MILLED) {
			if (board[11] == WHITE_STONE || board[11] == WHITE_STONE_MILLED) {
				if (L6 == false) {

					std::cout << "MILL FORMED : LINE 6" << std::endl;;;
					return L6 = true;
				}
			}
		}
	}

	if (board[11] == WHITE_STONE || board[11] == WHITE_STONE_MILLED) {
		if (board[12] == WHITE_STONE || board[12] == WHITE_STONE_MILLED) {
			if (board[13] == WHITE_STONE || board[13] == WHITE_STONE_MILLED) {
				if (L7 == false) {

					std::cout << "MILL FORMED : LINE 7" << std::endl;;;
					return L7 = true;
				}
			}
		}
	}


	if (board[13] == WHITE_STONE || board[13] == WHITE_STONE_MILLED) {
		if (board[14] == WHITE_STONE || board[14] == WHITE_STONE_MILLED) {
			if (board[15] == WHITE_STONE || board[15] == WHITE_STONE_MILLED) {
				if (L8 == false) {

					std::cout << "MILL FORMED : LINE 8" << std::endl;;;
					return L8 = true;
				}
			}
		}
	}

	if (board[23] == WHITE_STONE || board[23] == WHITE_STONE_MILLED) {
		if (board[16] == WHITE_STONE || board[16] == WHITE_STONE_MILLED) {
			if (board[17] == WHITE_STONE || board[17] == WHITE_STONE_MILLED) {
				if (L9 == false) {

					std::cout << "MILL FORMED : LINE 9" << std::endl;;;
					return L9 = true;
				}
			}
		}
	}

	if (board[17] == WHITE_STONE || board[17] == WHITE_STONE_MILLED) {
		if (board[18] == WHITE_STONE || board[18] == WHITE_STONE_MILLED) {
			if (board[19] == WHITE_STONE || board[19] == WHITE_STONE_MILLED) {
				if (L10 == false) {

					std::cout << "MILL FORMED : LINE 10" << std::endl;;;
					return L10 = true;
				}
			}
		}
	}

	if (board[19] == WHITE_STONE || board[19] == WHITE_STONE_MILLED) {
		if (board[20] == WHITE_STONE || board[20] == WHITE_STONE_MILLED) {
			if (board[21] == WHITE_STONE || board[21] == WHITE_STONE_MILLED) {
				if (L11 == false) {

					std::cout << "MILL FORMED : LINE 11" << std::endl;;;
					return L11 = true;
				}
			}
		}
	}

	if (board[21] == WHITE_STONE || board[21] == WHITE_STONE_MILLED) {
		if (board[22] == WHITE_STONE || board[22] == WHITE_STONE_MILLED) {
			if (board[23] == WHITE_STONE || board[23] == WHITE_STONE_MILLED) {
				if (L12 == false) {

					std::cout << "MILL FORMED : LINE 12" << std::endl;;;
					return L12 = true;
				}
			}
		}
	}

	if (board[7] == WHITE_STONE || board[7] == WHITE_STONE_MILLED) {
		if (board[8] == WHITE_STONE || board[8] == WHITE_STONE_MILLED) {
			if (board[16] == WHITE_STONE || board[16] == WHITE_STONE_MILLED) {
				if (L13 == false) {

					std::cout << "MILL FORMED : LINE 13" << std::endl;;;
					return L13 = true;
				}
			}
		}
	}

	if (board[1] == WHITE_STONE || board[1] == WHITE_STONE_MILLED) {
		if (board[10] == WHITE_STONE || board[10] == WHITE_STONE_MILLED) {
			if (board[18] == WHITE_STONE || board[18] == WHITE_STONE_MILLED) {
				if (L14 == false) {

					std::cout << "MILL FORMED : LINE 14" << std::endl;;;
					return L14 = true;
				}
			}
		}
	}

	if (board[3] == WHITE_STONE || board[3] == WHITE_STONE_MILLED) {
		if (board[12] == WHITE_STONE || board[12] == WHITE_STONE_MILLED) {
			if (board[20] == WHITE_STONE || board[20] == WHITE_STONE_MILLED) {
				if (L15 == false) {

					std::cout << "MILL FORMED : LINE 15" << std::endl;;;
					return L15 = true;
				}
			}
		}
	}

	if (board[5] == WHITE_STONE || board[5] == WHITE_STONE_MILLED) {
		if (board[14] == WHITE_STONE || board[14] == WHITE_STONE_MILLED) {
			if (board[22] == WHITE_STONE || board[22] == WHITE_STONE_MILLED) {
				if (L16 == false) {

					std::cout << "MILL FORMED : LINE 16" << std::endl;;;
					return L16 = true;
				}
			}
		}
	}
}

bool GameState::CheckMovesW(int board[]) {

	for (int i = 0 ; i < 24; i++) {

		if (board[i] == BLACK_STONE) {
			return false;
		}

	}
	return true;

}

bool GameState::CheckMovesB(int board[]) {

	for (int i = 0; i < 24; i++) {
		if (board[i] == WHITE_STONE) {
			return false;
		}

	}
	return true;

}

void GameState::ConvertMillBlack(int board[]) {

	if (L1) {
		if (board[0] == BLACK_STONE || board[0] == BLACK_STONE_MILLED) {
			if (board[1] == BLACK_STONE || board[1] == BLACK_STONE_MILLED) {
				if (board[2] == BLACK_STONE || board[2] == BLACK_STONE_MILLED) {
					board[0] = BLACK_STONE_MILLED;
					board[1] = BLACK_STONE_MILLED;
					board[2] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L2) {
		if (board[0] == BLACK_STONE || board[0] == BLACK_STONE_MILLED) {
			if (board[7] == BLACK_STONE || board[7] == BLACK_STONE_MILLED) {
				if (board[6] == BLACK_STONE || board[6] == BLACK_STONE_MILLED) {
					board[0] = BLACK_STONE_MILLED;
					board[7] = BLACK_STONE_MILLED;
					board[6] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L3) {
		if (board[2] == BLACK_STONE || board[2] == BLACK_STONE_MILLED) {
			if (board[3] == BLACK_STONE || board[3] == BLACK_STONE_MILLED) {
				if (board[4] == BLACK_STONE || board[4] == BLACK_STONE_MILLED) {
					board[2] = BLACK_STONE_MILLED;
					board[3] = BLACK_STONE_MILLED;
					board[4] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L4) {
		if (board[4] == BLACK_STONE || board[4] == BLACK_STONE_MILLED) {
			if (board[5] == BLACK_STONE || board[5] == BLACK_STONE_MILLED) {
				if (board[6] == BLACK_STONE || board[6] == BLACK_STONE_MILLED) {
					board[4] = BLACK_STONE_MILLED;
					board[5] = BLACK_STONE_MILLED;
					board[6] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L5) {
		if (board[15] == BLACK_STONE || board[15] == BLACK_STONE_MILLED) {
			if (board[8] == BLACK_STONE || board[8] == BLACK_STONE_MILLED) {
				if (board[9] == BLACK_STONE || board[9] == BLACK_STONE_MILLED) {
					board[15] = BLACK_STONE_MILLED;
					board[8] = BLACK_STONE_MILLED;
					board[9] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L6) {
		if (board[9] == BLACK_STONE || board[9] == BLACK_STONE_MILLED) {
			if (board[10] == BLACK_STONE || board[10] == BLACK_STONE_MILLED) {
				if (board[11] == BLACK_STONE || board[11] == BLACK_STONE_MILLED) {
					board[9] = BLACK_STONE_MILLED;
					board[10] = BLACK_STONE_MILLED;
					board[11] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L7) {
		if (board[11] == BLACK_STONE || board[11] == BLACK_STONE_MILLED) {
			if (board[12] == BLACK_STONE || board[12] == BLACK_STONE_MILLED) {
				if (board[13] == BLACK_STONE || board[13] == BLACK_STONE_MILLED) {
					board[11] = BLACK_STONE_MILLED;
					board[12] = BLACK_STONE_MILLED;
					board[13] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L8) {
		if (board[13] == BLACK_STONE || board[13] == BLACK_STONE_MILLED) {
			if (board[14] == BLACK_STONE || board[14] == BLACK_STONE_MILLED) {
				if (board[15] == BLACK_STONE || board[15] == BLACK_STONE_MILLED) {
					board[13] = BLACK_STONE_MILLED;
					board[14] = BLACK_STONE_MILLED;
					board[15] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L9) {
		if (board[23] == BLACK_STONE || board[23] == BLACK_STONE_MILLED) {
			if (board[16] == BLACK_STONE || board[24] == BLACK_STONE_MILLED) {
				if (board[17] == BLACK_STONE || board[25] == BLACK_STONE_MILLED) {
					board[23] = BLACK_STONE_MILLED;
					board[16] = BLACK_STONE_MILLED;
					board[17] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L10) {
		if (board[17] == BLACK_STONE || board[17] == BLACK_STONE_MILLED) {
			if (board[18] == BLACK_STONE || board[18] == BLACK_STONE_MILLED) {
				if (board[19] == BLACK_STONE || board[19] == BLACK_STONE_MILLED) {
					board[17] = BLACK_STONE_MILLED;
					board[18] = BLACK_STONE_MILLED;
					board[19] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L11) {
		if (board[19] == BLACK_STONE || board[19] == BLACK_STONE_MILLED) {
			if (board[20] == BLACK_STONE || board[20] == BLACK_STONE_MILLED) {
				if (board[21] == BLACK_STONE || board[21] == BLACK_STONE_MILLED) {
					board[19] = BLACK_STONE_MILLED;
					board[20] = BLACK_STONE_MILLED;
					board[21] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L12) {
		if (board[21] == BLACK_STONE || board[21] == BLACK_STONE_MILLED) {
			if (board[22] == BLACK_STONE || board[22] == BLACK_STONE_MILLED) {
				if (board[23] == BLACK_STONE || board[23] == BLACK_STONE_MILLED) {
					board[21] = BLACK_STONE_MILLED;
					board[22] = BLACK_STONE_MILLED;
					board[23] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L13) {
		if (board[7] == BLACK_STONE || board[7] == BLACK_STONE_MILLED) {
			if (board[8] == BLACK_STONE || board[8] == BLACK_STONE_MILLED) {
				if (board[16] == BLACK_STONE || board[16] == BLACK_STONE_MILLED) {
					board[7] = BLACK_STONE_MILLED;
					board[8] = BLACK_STONE_MILLED;
					board[16] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L14) {
		if (board[1] == BLACK_STONE || board[14] == BLACK_STONE_MILLED) {
			if (board[10] == BLACK_STONE || board[10] == BLACK_STONE_MILLED) {
				if (board[18] == BLACK_STONE || board[18] == BLACK_STONE_MILLED) {
					board[1] = BLACK_STONE_MILLED;
					board[10] = BLACK_STONE_MILLED;
					board[18] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L15) {
		if (board[3] == BLACK_STONE || board[3] == BLACK_STONE_MILLED) {
			if (board[12] == BLACK_STONE || board[12] == BLACK_STONE_MILLED) {
				if (board[20] == BLACK_STONE || board[20] == BLACK_STONE_MILLED) {
					board[3] = BLACK_STONE_MILLED;
					board[12] = BLACK_STONE_MILLED;
					board[20] = BLACK_STONE_MILLED;
				}
			}
		}
	}

	if (L16) {
		if (board[5] == BLACK_STONE || board[5] == BLACK_STONE_MILLED) {
			if (board[14] == BLACK_STONE || board[14] == BLACK_STONE_MILLED) {
				if (board[22] == BLACK_STONE || board[22] == BLACK_STONE_MILLED) {
					board[5] = BLACK_STONE_MILLED;
					board[14] = BLACK_STONE_MILLED;
					board[22] = BLACK_STONE_MILLED;
				}
			}
		}
	}
}

void GameState::UnConvertMillBlack(int board[], int x) {
	if (x == 0 || x == 1 || x == 2) {
		if (L1) {
			if (board[0] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[1] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[2] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[0] = BLACK_STONE;
						board[1] = BLACK_STONE;
						board[2] = BLACK_STONE;
						L1 = false;
					}
				}
			}
		}
	}

	if (x == 0 || x == 7 || x == 6) {
		if (L2) {
			if (board[0] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[7] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[6] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[0] = BLACK_STONE;
						board[7] = BLACK_STONE;
						board[6] = BLACK_STONE;
						L2 = false;
					}
				}
			}
		}
	}

	if (x == 2 || x == 3 || x == 4) {
		if (L3) {
			if (board[2] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[3] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[4] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[2] = BLACK_STONE;
						board[3] = BLACK_STONE;
						board[4] = BLACK_STONE;
						L3 = false;
					}
				}
			}
		}
	}
	if (x == 4 || x == 5 || x == 6) {
		if (L4) {
			if (board[4] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[5] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[6] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[4] = BLACK_STONE;
						board[5] = BLACK_STONE;
						board[6] = BLACK_STONE;
						L4 = false;
					}
				}
			}
		}
	}

	if (x == 15 || x == 8 || x == 9) {
		if (L5) {
			if (board[15] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[8] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[9] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[15] = BLACK_STONE;
						board[8] = BLACK_STONE;
						board[9] = BLACK_STONE;
						L5 = false;
					}
				}
			}
		}
	}

	if (x == 9 || x == 10 || x == 11) {
		if (L6) {
			if (board[9] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[10] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[11] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[9] = BLACK_STONE;
						board[10] = BLACK_STONE;
						board[11] = BLACK_STONE;
						L6 = false;
					}
				}
			}
		}
	}

	if (x == 11 || x == 12 || x == 13) {
		if (L7) {
			if (board[11] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[12] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[13] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[11] = BLACK_STONE;
						board[12] = BLACK_STONE;
						board[13] = BLACK_STONE;
						L7 = false;
					}
				}
			}
		}
	}

	if (x == 13 || x == 14 || x == 15) {
		if (L8) {
			if (board[13] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[14] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[15] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[13] = BLACK_STONE;
						board[14] = BLACK_STONE;
						board[15] = BLACK_STONE;
						L8 = false;
					}
				}
			}
		}
	}

	if (x == 23 || x == 16 || x == 17) {
		if (L9) {
			if (board[23] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[16] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[17] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[23] = BLACK_STONE;
						board[16] = BLACK_STONE;
						board[17] = BLACK_STONE;
						L9 = false;
					}
				}
			}
		}
	}

	if (x == 17 || x == 18 || x == 19) {
		if (L10) {
			if (board[17] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[18] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[19] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[17] = BLACK_STONE;
						board[18] = BLACK_STONE;
						board[19] = BLACK_STONE;
						L10 = false;
					}
				}
			}
		}
	}

	if (x == 19 || x == 20 || x == 21) {
		if (L11) {
			if (board[19] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[20] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[21] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[19] = BLACK_STONE;
						board[20] = BLACK_STONE;
						board[21] = BLACK_STONE;
						L11 = false;
					}
				}
			}
		}
	}

	if (x == 21 || x == 22 || x == 23) {
		if (L12) {
			if (board[21] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[22] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[23] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[21] = BLACK_STONE;
						board[22] = BLACK_STONE;
						board[23] = BLACK_STONE;
						L12 = false;
					}
				}
			}
		}
	}

	if (x == 7 || x == 8 || x == 16) {
		if (L13) {
			if (board[7] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[8] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[16] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[7] = BLACK_STONE;
						board[8] = BLACK_STONE;
						board[16] = BLACK_STONE;
						L13 = false;
					}
				}
			}
		}
	}

	if (x == 1 || x == 10 || x == 18) {
		if (L14) {
			if (board[1] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[10] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[18] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[1] = BLACK_STONE;
						board[10] = BLACK_STONE;
						board[18] = BLACK_STONE;
						L14 = false;
					}
				}
			}
		}
	}
	if (x == 3 || x == 12 || x == 20) {
		if (L15) {
			if (board[3] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[12] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[20] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[3] = BLACK_STONE;
						board[12] = BLACK_STONE;
						board[20] = BLACK_STONE;
						L15 = false;
					}
				}
			}
		}
	}

	if (x == 5 || x == 14 || x == 22) {
		if (L16) {
			if (board[5] == BLACK_STONE_MILLED || BLACK_STONE) {
				if (board[14] == BLACK_STONE_MILLED || BLACK_STONE) {
					if (board[22] == BLACK_STONE_MILLED || BLACK_STONE) {
						board[5] = BLACK_STONE;
						board[14] = BLACK_STONE;
						board[22] = BLACK_STONE;
						L16 = false;
					}
				}
			}
		}
	}
}

void GameState::ConvertMillWhite(int board[]) {

	if (L1) {
	if (board[0] == WHITE_STONE || board[0] == WHITE_STONE_MILLED) {
		if (board[1] == WHITE_STONE || board[1] == WHITE_STONE_MILLED) {
			if (board[2] == WHITE_STONE || board[2] == WHITE_STONE_MILLED) {
				board[0] = WHITE_STONE_MILLED;
				board[1] = WHITE_STONE_MILLED;
				board[2] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L2) {
	if (board[0] == WHITE_STONE || board[0] == WHITE_STONE_MILLED) {
		if (board[7] == WHITE_STONE || board[7] == WHITE_STONE_MILLED) {
			if (board[6] == WHITE_STONE || board[6] == WHITE_STONE_MILLED) {
				board[0] = WHITE_STONE_MILLED;
				board[7] = WHITE_STONE_MILLED;
				board[6] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L3) {
	if (board[2] == WHITE_STONE || board[2] == WHITE_STONE_MILLED) {
		if (board[3] == WHITE_STONE || board[3] == WHITE_STONE_MILLED) {
			if (board[4] == WHITE_STONE || board[4] == WHITE_STONE_MILLED) {
				board[2] = WHITE_STONE_MILLED;
				board[3] = WHITE_STONE_MILLED;
				board[4] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L4) {
	if (board[4] == WHITE_STONE || board[4] == WHITE_STONE_MILLED) {
		if (board[5] == WHITE_STONE || board[5] == WHITE_STONE_MILLED) {
			if (board[6] == WHITE_STONE || board[6] == WHITE_STONE_MILLED) {
				board[4] = WHITE_STONE_MILLED;
				board[5] = WHITE_STONE_MILLED;
				board[6] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L5) {
	if (board[15] == WHITE_STONE || board[15] == WHITE_STONE_MILLED) {
		if (board[8] == WHITE_STONE || board[8] == WHITE_STONE_MILLED) {
			if (board[9] == WHITE_STONE || board[9] == WHITE_STONE_MILLED) {
				board[15] = WHITE_STONE_MILLED;
				board[8] = WHITE_STONE_MILLED;
				board[9] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L6) {
	if (board[9] == WHITE_STONE || board[9] == WHITE_STONE_MILLED) {
		if (board[10] == WHITE_STONE || board[10] == WHITE_STONE_MILLED) {
			if (board[11] == WHITE_STONE || board[11] == WHITE_STONE_MILLED) {
				board[9] = WHITE_STONE_MILLED;
				board[10] = WHITE_STONE_MILLED;
				board[11] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L7) {
	if (board[11] == WHITE_STONE || board[11] == WHITE_STONE_MILLED) {
		if (board[12] == WHITE_STONE || board[12] == WHITE_STONE_MILLED) {
			if (board[13] == WHITE_STONE || board[13] == WHITE_STONE_MILLED) {
				board[11] = WHITE_STONE_MILLED;
				board[12] = WHITE_STONE_MILLED;
				board[13] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L8) {
	if (board[13] == WHITE_STONE || board[13] == WHITE_STONE_MILLED) {
		if (board[14] == WHITE_STONE || board[14] == WHITE_STONE_MILLED) {
			if (board[15] == WHITE_STONE || board[15] == WHITE_STONE_MILLED) {
				board[13] = WHITE_STONE_MILLED;
				board[14] = WHITE_STONE_MILLED;
				board[15] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L9) {
	if (board[23] == WHITE_STONE || board[23] == WHITE_STONE_MILLED) {
		if (board[16] == WHITE_STONE || board[24] == WHITE_STONE_MILLED) {
			if (board[17] == WHITE_STONE || board[25] == WHITE_STONE_MILLED) {
				board[23] = WHITE_STONE_MILLED;
				board[16] = WHITE_STONE_MILLED;
				board[17] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L10) {
	if (board[17] == WHITE_STONE || board[17] == WHITE_STONE_MILLED) {
		if (board[18] == WHITE_STONE || board[18] == WHITE_STONE_MILLED) {
			if (board[19] == WHITE_STONE || board[19] == WHITE_STONE_MILLED) {
				board[17] = WHITE_STONE_MILLED;
				board[18] = WHITE_STONE_MILLED;
				board[19] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L11) {
	if (board[19] == WHITE_STONE || board[19] == WHITE_STONE_MILLED) {
		if (board[20] == WHITE_STONE || board[20] == WHITE_STONE_MILLED) {
			if (board[21] == WHITE_STONE || board[21] == WHITE_STONE_MILLED) {
				board[19] = WHITE_STONE_MILLED;
				board[20] = WHITE_STONE_MILLED;
				board[21] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L12) {
	if (board[21] == WHITE_STONE || board[21] == WHITE_STONE_MILLED) {
		if (board[22] == WHITE_STONE || board[22] == WHITE_STONE_MILLED) {
			if (board[23] == WHITE_STONE || board[23] == WHITE_STONE_MILLED) {
				board[21] = WHITE_STONE_MILLED;
				board[22] = WHITE_STONE_MILLED;
				board[23] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L13) {
	if (board[7] == WHITE_STONE || board[7] == WHITE_STONE_MILLED) {
		if (board[8] == WHITE_STONE || board[8] == WHITE_STONE_MILLED) {
			if (board[16] == WHITE_STONE || board[16] == WHITE_STONE_MILLED) {
				board[7] = WHITE_STONE_MILLED;
				board[8] = WHITE_STONE_MILLED;
				board[16] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L14) {
	if (board[1] == WHITE_STONE || board[14] == WHITE_STONE_MILLED) {
		if (board[10] == WHITE_STONE || board[10] == WHITE_STONE_MILLED) {
			if (board[18] == WHITE_STONE || board[18] == WHITE_STONE_MILLED) {
				board[1] = WHITE_STONE_MILLED;
				board[10] = WHITE_STONE_MILLED;
				board[18] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L15) {
	if (board[3] == WHITE_STONE || board[3] == WHITE_STONE_MILLED) {
		if (board[12] == WHITE_STONE || board[12] == WHITE_STONE_MILLED) {
			if (board[20] == WHITE_STONE || board[20] == WHITE_STONE_MILLED) {
				board[3] = WHITE_STONE_MILLED;
				board[12] = WHITE_STONE_MILLED;
				board[20] = WHITE_STONE_MILLED;
			}
		}
	}
}

if (L16) {
	if (board[5] == WHITE_STONE || board[5] == WHITE_STONE_MILLED) {
		if (board[14] == WHITE_STONE || board[14] == WHITE_STONE_MILLED) {
			if (board[22] == WHITE_STONE || board[22] == WHITE_STONE_MILLED) {
				board[5] = WHITE_STONE_MILLED;
				board[14] = WHITE_STONE_MILLED;
				board[22] = WHITE_STONE_MILLED;
			}
		}
	}
}
}

void GameState::UnConvertMillWhite(int board[], int x) {
	if (x == 0 || x == 1 || x == 2) {
		if (L1) {
			if (board[0] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[1] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[2] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[0] = WHITE_STONE;
						board[1] = WHITE_STONE;
						board[2] = WHITE_STONE;
						L1 = false;
					}
				}
			}
		}
	}

	if (x == 0 || x == 7 || x == 6) {
		if (L2) {
			if (board[0] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[7] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[6] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[0] = WHITE_STONE;
						board[7] = WHITE_STONE;
						board[6] = WHITE_STONE;
						L2 = false;
					}
				}
			}
		}
	}

	if (x == 2 || x == 3 || x == 4) {
		if (L3) {
			if (board[2] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[3] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[4] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[2] = WHITE_STONE;
						board[3] = WHITE_STONE;
						board[4] = WHITE_STONE;
						L3 = false;
					}
				}
			}
		}
	}
	if (x == 4 || x == 5 || x == 6) {
		if (L4) {
			if (board[4] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[5] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[6] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[4] = WHITE_STONE;
						board[5] = WHITE_STONE;
						board[6] = WHITE_STONE;
						L4 = false;
					}
				}
			}
		}
	}

	if (x == 15 || x == 8 || x == 9) {
		if (L5) {
			if (board[15] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[8] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[9] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[15] = WHITE_STONE;
						board[8] = WHITE_STONE;
						board[9] = WHITE_STONE;
						L5 = false;
					}
				}
			}
		}
	}

	if (x == 9 || x == 10 || x == 11) {
		if (L6) {
			if (board[9] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[10] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[11] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[9] = WHITE_STONE;
						board[10] = WHITE_STONE;
						board[11] = WHITE_STONE;
						L6 = false;
					}
				}
			}
		}
	}

	if (x == 11 || x == 12 || x == 13) {
		if (L7) {
			if (board[11] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[12] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[13] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[11] = WHITE_STONE;
						board[12] = WHITE_STONE;
						board[13] = WHITE_STONE;
						L7 = false;
					}
				}
			}
		}
	}

	if (x == 13 || x == 14 || x == 15) {
		if (L8) {
			if (board[13] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[14] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[15] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[13] = WHITE_STONE;
						board[14] = WHITE_STONE;
						board[15] = WHITE_STONE;
						L8 = false;
					}
				}
			}
		}
	}

	if (x == 23 || x == 16 || x == 17) {
		if (L9) {
			if (board[23] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[16] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[17] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[23] = WHITE_STONE;
						board[16] = WHITE_STONE;
						board[17] = WHITE_STONE;
						L9 = false;
					}
				}
			}
		}
	}

	if (x == 17 || x == 18 || x == 19) {
		if (L10) {
			if (board[17] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[18] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[19] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[17] = WHITE_STONE;
						board[18] = WHITE_STONE;
						board[19] = WHITE_STONE;
						L10 = false;
					}
				}
			}
		}
	}

	if (x == 19 || x == 20 || x == 21) {
		if (L11) {
			if (board[19] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[20] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[21] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[19] = WHITE_STONE;
						board[20] = WHITE_STONE;
						board[21] = WHITE_STONE;
						L11 = false;
					}
				}
			}
		}
	}

	if (x == 21 || x == 22 || x == 23) {
		if (L12) {
			if (board[21] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[22] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[23] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[21] = WHITE_STONE;
						board[22] = WHITE_STONE;
						board[23] = WHITE_STONE;
						L12 = false;
					}
				}
			}
		}
	}

	if (x == 7 || x == 8 || x == 16) {
		if (L13) {
			if (board[7] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[8] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[16] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[7] = WHITE_STONE;
						board[8] = WHITE_STONE;
						board[16] = WHITE_STONE;
						L13 = false;
					}
				}
			}
		}
	}

	if (x == 1 || x == 10 || x == 18) {
		if (L14) {
			if (board[1] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[10] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[18] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[1] = WHITE_STONE;
						board[10] = WHITE_STONE;
						board[18] = WHITE_STONE;
						L14 = false;
					}
				}
			}
		}
	}
	if (x == 3 || x == 12 || x == 20) {
		if (L15) {
			if (board[3] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[12] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[20] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[3] = WHITE_STONE;
						board[12] = WHITE_STONE;
						board[20] = WHITE_STONE;
						L15 = false;
					}
				}
			}
		}
	}

	if (x == 5 || x == 14 || x == 22) {
		if (L16) {
			if (board[5] == WHITE_STONE_MILLED || WHITE_STONE) {
				if (board[14] == WHITE_STONE_MILLED || WHITE_STONE) {
					if (board[22] == WHITE_STONE_MILLED || WHITE_STONE) {
						board[5] = WHITE_STONE;
						board[14] = WHITE_STONE;
						board[22] = WHITE_STONE;
						L16 = false;
					}
				}
			}
		}
	}
}

void GameState::CheckAndPlace(int x) {


	if (boardArray[x] == EMPTY_PIECE && p2coin > 0)

	{

		if (P1 == turn) {

			boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
			boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
			boardArray[x] = BLACK_STONE;
			p1coin -= 1;
			DecerementImageB(counterB, p1coin);
			
			std::cout << "PLAYER 1 STONES: " << p1coin << std::endl;

			if (CheckMill(boardArray) == true) {
				ConvertMillBlack(boardArray);
				remove_phase = true;
			}
			else {
				turn = P2;
			}
		}

		else if (P2 == turn) {


			boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
			boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
			boardArray[x] = WHITE_STONE;

			p2coin -= 1;
			DecerementImageW(counterW, p2coin);
			std::cout << "PLAYER 2 STONES: " << p2coin << std::endl;

			if (CheckMill(boardArray) == true) {
				ConvertMillWhite(boardArray);
				remove_phase = true;
			}
			else {
				turn = P1;
			}

		}
		if (p1coin == 0) {
			if (p2coin == 0) {
				fly_phase = true;
			}
		}
	}
}

bool GameState::AdjacentOpen(int board[], int x) {

	if (x == 0) {
		if (board[7] == EMPTY_PIECE || board[1] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 1) {
		if (board[0] == EMPTY_PIECE || board[2] == EMPTY_PIECE || board[10] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 2) {
		if (board[1] == EMPTY_PIECE || board[3] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 3) {
		if (board[2] == EMPTY_PIECE || board[4] == EMPTY_PIECE || board[12] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 4) {
		if (board[3] == EMPTY_PIECE || board[5] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 5) {
		if (board[4] == EMPTY_PIECE || board[6] == EMPTY_PIECE || board[14] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 6) {
		if (board[5] == EMPTY_PIECE || board[7] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 7) {
		if (board[6] == EMPTY_PIECE || board[0] == EMPTY_PIECE || board[8] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 8) {
		if (board[9] == EMPTY_PIECE || board[7] == EMPTY_PIECE || board[15] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 9) {
		if (board[10] == EMPTY_PIECE || board[8] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 10) {
		if (board[9] == EMPTY_PIECE || board[11] == EMPTY_PIECE || board[1] == EMPTY_PIECE || board[18] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 11) {
		if (board[10] == EMPTY_PIECE || board[12] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 12) {
		if (board[11] == EMPTY_PIECE || board[13] == EMPTY_PIECE || board[3] == EMPTY_PIECE || board[20] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 13) {
		if (board[12] == EMPTY_PIECE || board[14] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 14) {
		if (board[13] == EMPTY_PIECE || board[15] == EMPTY_PIECE || board[22] == EMPTY_PIECE || board[5] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 15) {
		if (board[14] == EMPTY_PIECE || board[8] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 16) {
		if (board[17] == EMPTY_PIECE || board[23] == EMPTY_PIECE || board[8] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 17) {
		if (board[16] == EMPTY_PIECE || board[18] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 18) {
		if (board[17] == EMPTY_PIECE || board[10] == EMPTY_PIECE || board[19] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 19) {
		if (board[18] == EMPTY_PIECE || board[20] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 20) {
		if (board[19] == EMPTY_PIECE || board[12] == EMPTY_PIECE || board[21] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 21) {
		if (board[20] == EMPTY_PIECE || board[22] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 22) {
		if (board[21] == EMPTY_PIECE || board[14] == EMPTY_PIECE || board[23] == EMPTY_PIECE) {
			return true;
		}
	}

	if (x == 23) {
		if (board[22] == EMPTY_PIECE || board[16] == EMPTY_PIECE) {
			return true;
		}
	}

	else {
		return false;
	}
}

bool GameState::IsAdjacent(int x, int y) {

	if (x == 0) {
		if (y == 1 || y == 7) {

			return true;
		}
	}

	if (x == 1) {
		if (y == 0 || y == 2 || y == 10) {

			return true;
		}
	}

	if (x == 2) {
		if (y == 1 || y == 3) {

			return true;
		}
	}

	if (x == 3) {
		if (y == 2 || y == 4 || y == 12) {

			return true;
		}
	}

	if (x == 4) {
		if (y == 3 || y == 5) {

			return true;
		}
	}

	if (x == 5) {
		if (y == 4 || y == 14 || y == 6) {

			return true;
		}
	}

	if (x == 6) {
		if (y == 5 || y == 7) {

			return true;
		}
	}

	if (x == 7) {
		if (y == 6 || y == 8 || y == 0) {

			return true;
		}
	}

	if (x == 8) {
		if (y == 15 || y == 16 || y == 9 || y == 7) {

			return true;
		}
	}

	if (x == 9) {
		if (y == 8 || y == 10) {

			return true;
		}
	}

	if (x == 10) {
		if (y == 1 || y == 9 || y == 11 || y == 18) {

			return true;
		}
	}

	if (x == 11) {
		if (y == 10 || y == 12) {

			return true;
		}
	}

	if (x == 12) {
		if (y == 13 || y == 3 || y == 11 || y == 20) {

			return true;
		}
	}

	if (x == 13) {
		if (y == 12 || y == 14) {

			return true;
		}
	}

	if (x == 14) {
		if (y == 22 || y == 13 || y == 15 || y == 5) {

			return true;
		}
	}

	if (x == 15) {
		if (y == 14 || y == 8) {

			return true;
		}
	}

	if (x == 16) {
		if (y == 23 || y == 17 || y == 8) {

			return true;
		}
	}

	if (x == 17) {
		if (y == 16 || y == 18) {

			return true;
		}
	}

	if (x == 18) {
		if (y == 17 || y == 10 || y == 19) {

			return true;
		}
	}

	if (x == 19) {
		if (y == 20 || y == 18) {

			return true;
		}
	}

	if (x == 20) {
		if (y == 19 || y == 21 || y == 12) {

			return true;
		}
	}

	if (x == 21) {
		if (y == 20 || y == 22) {

			return true;
		}
	}

	if (x == 22) {
		if (y == 21 || y == 23 || y == 14) {

			return true;
		}
	}

	if (x == 23) {
		if (y == 22 || y == 16) {

			return true;
		}
	}
}

void GameState::CheckAndDelete(int x) {


	if (boardArray[x] != EMPTY_PIECE )
	{

		if (P1 == turn) {
			no_legal_moves = CheckMovesB(boardArray);
			if (boardArray[x] == WHITE_STONE) {
				boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
				boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
				boardArray[x] = EMPTY_PIECE;
				p2total -= 1;

				if (boardArray[x] == EMPTY_PIECE) {
					remove_phase = false;
					turn = P2;
				}
			}

			else if (boardArray[x] == WHITE_STONE_MILLED) {
				if (no_legal_moves == true) {
					boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
					UnConvertMillWhite(boardArray, x);
					boardArray[x] = EMPTY_PIECE;
					p2total -= 1;

					if (boardArray[x] == EMPTY_PIECE) {
						remove_phase = false;
						no_legal_moves = false;
						turn = P2;
					}
				}
				else {
					return;
				}
			}
		}
			
		else if (P2 == turn) {
			no_legal_moves = CheckMovesW(boardArray);
			if (boardArray[x] == BLACK_STONE) {
				boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
				boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
				boardArray[x] = EMPTY_PIECE;
				p1total -= 1;

				if (boardArray[x] == EMPTY_PIECE) {
					remove_phase = false;
					turn = P1;
				}
			}
			else if (boardArray[x] == BLACK_STONE_MILLED) {
				if (no_legal_moves == true) {
					boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 255, 0));
					UnConvertMillBlack(boardArray, x);
					no_legal_moves = false;
					boardArray[x] = EMPTY_PIECE;
					p2total -= 1;

					if (boardArray[x] == EMPTY_PIECE) {
						remove_phase = false;
						no_legal_moves = false;
						turn = P1;
						
					}
				}
				else {
					return;
				}
			}
		}


		if (p1total == 2) {
			int p1coin = 9;
			int p2coin = 9;
			int p1total = 9;
			int p2total = 9;
			this->_data->machine.AddState(StateRef(new GameOverW(_data)), true);

		}
		if (p2total == 2) {
			int p1coin = 9;
			int p2coin = 9;
			int p1total = 9;
			int p2total = 9;
			this->_data->machine.AddState(StateRef(new GameOverB(_data)), true);

		}

	}
}

void GameState::SelectCoin(int x) {


	if (boardArray[x] != EMPTY_PIECE) {

		if (P1 == turn) {
			if (p1total > 3) {
				if (AdjacentOpen(boardArray, x) == true) {
					if (boardArray[x] == BLACK_STONE || boardArray[x] == BLACK_STONE_MILLED) {
						std::cout << "Changing BLACK to HIGHLIGHT >3" << std::endl;
						boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
						boardPieces[x].setColor(sf::Color(255, 255, 0, 255));
						UnConvertMillBlack(boardArray, x);

						select = true;
						old_pos = x;
					}
				}

				else {
					return;
				}
			}
			if (p1total <= 3) {
				if (boardArray[x] == BLACK_STONE || boardArray[x] == BLACK_STONE_MILLED) {
					std::cout << "Changing BLACK to HIGHLIGHT <3 " << std::endl;
					boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 0, 255));
					UnConvertMillBlack(boardArray, x);

					select = true;
					old_pos = x;
				}
			}
		}

		else if (P2 == turn) {
			if (p2total > 3) {
				if (AdjacentOpen(boardArray, x) == true) {
					if (boardArray[x] == WHITE_STONE || boardArray[x] == WHITE_STONE_MILLED) {
						std::cout << "Changing WHITE to HIGHLIGHT" << std::endl;
						boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
						boardPieces[x].setColor(sf::Color(255, 255, 0, 255));
						UnConvertMillWhite(boardArray, x);

						select = true;
						old_pos = x;
					}
				}
				else {
					return;
				}
			}
			if (p2total <= 3) {
				if (boardArray[x] == WHITE_STONE || boardArray[x] == WHITE_STONE_MILLED) {
					std::cout << "Changing WHITE to HIGHLIGHT" << std::endl;
					boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 0, 255));
					UnConvertMillWhite(boardArray, x);

					select = true;
					old_pos = x;
				}
			}
		}
	}
}

void GameState::MoveCoin(int x) {

	std::cout << "p1 " << (p1total) << std::endl;
	std::cout << "p2 " << (p2total) << std::endl;

		if (boardArray[x] == EMPTY_PIECE) {

		if (P1 == turn) {
			if (p1total > 3) {
				if (IsAdjacent(old_pos, x) == true) {
					boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
					boardArray[x] = BLACK_STONE;

					boardPieces[old_pos].setTexture(this->_data->assets.GetTexture("bstone"));
					boardPieces[old_pos].setColor(sf::Color(255, 255, 255, 0));
					boardArray[old_pos] = EMPTY_PIECE;

					if (CheckMill(boardArray) == true) {
						ConvertMillBlack(boardArray);
						remove_phase = true;
					}

					else {
						std::cout << "WHITE TURN " << std::endl;
						turn = P2;
					}
				}
				else {
					return;
				}
			}
			if (p1total <= 3) {
				boardPieces[x].setTexture(this->_data->assets.GetTexture("bstone"));
				boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
				boardArray[x] = BLACK_STONE;

				boardPieces[old_pos].setTexture(this->_data->assets.GetTexture("bstone"));
				boardPieces[old_pos].setColor(sf::Color(255, 255, 255, 0));
				boardArray[old_pos] = EMPTY_PIECE;

				if (CheckMill(boardArray) == true) {
					ConvertMillBlack(boardArray);
					remove_phase = true;
				}

				else {
					std::cout << "WHITE TURN " << std::endl;
					turn = P2;
				}
			}
		}

		else if (P2 == turn) {
			if (p2total > 3) {
				if (IsAdjacent(old_pos, x) == true) {
					boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
					boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
					boardArray[x] = WHITE_STONE;

					boardPieces[old_pos].setTexture(this->_data->assets.GetTexture("wstone"));
					boardPieces[old_pos].setColor(sf::Color(255, 255, 255, 0));
					boardArray[old_pos] = EMPTY_PIECE;

					if (CheckMill(boardArray) == true) {
						ConvertMillWhite(boardArray);
						remove_phase = true;
					}

					else {
						std::cout << "BLACK TURN " << std::endl;
						turn = P1;
					}
				}
				else {
					return;
				}
			}
			if (p2total <= 3) {
				boardPieces[x].setTexture(this->_data->assets.GetTexture("wstone"));
				boardPieces[x].setColor(sf::Color(255, 255, 255, 255));
				boardArray[x] = WHITE_STONE;

				boardPieces[old_pos].setTexture(this->_data->assets.GetTexture("wstone"));
				boardPieces[old_pos].setColor(sf::Color(255, 255, 255, 0));
				boardArray[old_pos] = EMPTY_PIECE;

				if (CheckMill(boardArray) == true) {
					ConvertMillWhite(boardArray);
					remove_phase = true;
				}

				else {
					std::cout << "BLACK TURN " << std::endl;
					turn = P1;
				}
			}
		}
		select = false;
	}
}



