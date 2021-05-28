void GameState::UnConvertMillWHITE(int board[], int x) {
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