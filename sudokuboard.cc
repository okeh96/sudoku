/******************************************************************************
 * sudokuboard.cc                                                             *
 *                                               							  *
 * Completed by:  Oliver Keh                                                  *
 *                                                                            *
 * February 26, 2016                                                          *
 *                                                                            *
 * This file holds the function definitions for the sudoku board that help to *
 * decide whether a number can be placed onto the board, as well as other     *
 * necessary tools. 														  *
 *****************************************************************************/

#include "sudokuboard.h"

// Checks rows and columns as well as the surrounding 8 squares to see if it
// can place a number.
bool sudokuboard::canPlace(size_t r, size_t c, char n) const {

	// Checks specific spot, row, and column for number and returns false if 
	//it finds it.
	for (size_t i = 0; i <= 8; i++) {
		if (size_board[r][c] != '_' or size_board[r][i] == n or 
			size_board[i][c] == n) {
			return false;
		}
	}
    
    // Algorith for finding 9-box squares
	size_t r_ = r / 3 * 3;
	size_t c_ = c / 3 * 3;
     
    // Checks the 8 other boxes in a specific 9-box square for that number.
	for (size_t dr = 0; dr < 3; dr++) {
		for (size_t dc = 0; dc < 3; dc++) {
			if (size_board[r_ + dr][c_ + dc] == n) {
				return false;
			}
		}
	}

	// If all tests pass, the function returns true.
	return true;
}

// Constructor for board.
sudokuboard::sudokuboard() {
	// Initializes size to 9
	size = 9;
	// Prints 9 rows of 9 '_' characters
	for (size_t row_num = 0; row_num < 9; row_num++) {
		size_board[row_num] = "_________";
	}
}

// Placing numbers.
void sudokuboard::place(size_t r, size_t c, char n) {
	// Places n at a specific spot.s
	size_board[r][c] = n;
}

// Printing board.
void sudokuboard::print() const {
	// Prints board by row.
	for (size_t row_num = 0; row_num < 9; row_num++)
		cout << size_board[row_num] << endl;
}

// Get value at spot.
char sudokuboard::get(size_t r, size_t c) const {
	// returns value at a specific spot.
    return size_board[r][c];
}

// Replaces a value with '_'.
void sudokuboard::remove(size_t r, size_t c) {
	size_board[r][c] = '_';
}

// Checks if board is solved.
bool sudokuboard::solved() const {
	for (size_t r = 0; r < 9; r++) {
		for (size_t c = 0; c < 9; c++) {
			// Returns false if it finds a blank spot.
			if (size_board[r][c] == '_') {
				return false;
			}
		}
	}
	return true;
}