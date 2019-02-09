#pragma once

#ifndef Const
#define Const
const int PAWN_ID = 1;
const int BISHOP_ID = 2;
const int QUEEN_ID = 3;
const int KING_ID = 4;
const int KNIGHT_ID = 5;
const int ROOK_ID = 6;
const int DEFALT_ID = 7;
const int PAWN_VALUE = 1;
const int BISHOP_VALUE = 3;
const int QUEEN_VALUE = 9;
const int KING_VALUE = 3;
const int KNIGHT_VALUE = 3;
const int ROOK_VALUE = 6;

const int IMAGE_SCALE = 40;

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

const bool BLACK_PEICE = false;
const bool WHITE_PEICE = true;


// Checks if the x and y would be within the bounds of the board
inline bool ON_BOARD(int x, int y) {
	if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
		return true;
	}
	return false;
}

// Converts a x and y posistion to a vector position
inline int CONVERT_TO_ID(int x, int y) {
	if (ON_BOARD(x, y)) {
		return x * BOARD_HEIGHT + y;
	}
	return 0;
}
#endif