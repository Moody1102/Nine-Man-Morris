#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"


class GameState : public State
{
public:
	GameState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:

	void InitBoardPieces();
	void DecerementImageW(sf::Sprite, int y);
	void DecerementImageB(sf::Sprite, int y);
	void CheckAndPlace(int x);
	void CheckAndDelete(int x);

	void ConvertMillBlack(int board[]);
	void UnConvertMillBlack(int board[], int x);

	void ConvertMillWhite(int board[]);
	void UnConvertMillWhite(int board[], int x);


	void SelectCoin(int x);
	void MoveCoin(int x);

	bool AdjacentOpen(int board[], int x);
	bool IsAdjacent(int x, int y);

	int CheckPos(int x, int y);
	bool CheckMovesW(int board[]);
	bool CheckMovesB(int board[]);

	bool CheckMill(int board[]);

	GameDataRef _data;

	sf::Sprite background;
	sf::Sprite bstone;
	sf::Sprite wstone;
	sf::Sprite counterW;
	sf::Sprite counterB;

	sf::Sprite boardPieces[24];
	int boardArray[24];

	int turn;
	int gameState;
};