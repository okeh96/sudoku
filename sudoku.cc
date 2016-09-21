/******************************************************************************
 * sudoku.cc                                                                  *
 *                                                                            *
 * Completed by:  Oliver Keh                                                  *
 *                                                                            *
 * February 26, 2016                                                          *
 *                                                                            *
 * This file takes an input of an unfinished sudoku board and solves it using *
 * backtracking (which is defined in this file) and other functions defined in*
 * the other files. 
 *****************************************************************************/

#include <iostream>
#include <cstdlib>
#include "sudokuboard.h"
#include "stack.h"

using namespace std;

/*#########################################################################
  At a given position, this function goes through all 9 numbers from 1 to 9
  and stops as soon as it finds the first number that fits at that position.
  It then returns the number that fits in that position.
  ########################################################################*/

char find_low(const sudokuboard & brd, size_t & row, size_t & col,
                     char & num) {

    // Cycles through numbers 1 to 9 in a position and returns the lowest first
    // fit.
    for (char poss_num = '1'; poss_num <= '9'; poss_num++) {
        if (brd.canPlace(row, col, poss_num)) {
            return poss_num;
        }
    }
    // Function will never return 0 because code before will always place
    // something.
    return '0';
}

/*#########################################################################
  Determine the location of the most constrained empty cell on the board
  where the fewest numerals can be placed. Return true if one can be found
  and set row, col. Also set numeral the smallest numeral that can be placed 
  there ff any cell accepts 0 numerals, return false to trigger backtracking
  ##########################################################################*/

bool mostConstrained(const sudokuboard & brd, size_t & row, size_t & col,
                     char & numeral) {
    // Smallest keeps track of the most constrained spot on the board.
    size_t smallest = 9;

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            // For every new spot on the board, current is set back to 0.
            // Current counter keeps track of how many numbers fit into spot.
            size_t current = 0;
            // Makes sure spot is empty.
            if (brd.get(i, j) == '_') {
                // Tries to place numbers from 1-9 and increases current by 1
                // every time it finds a possible entry number.
                for (char n = '1'; n <= '9'; n++) {
                    if (brd.canPlace(i, j, n)) {
                        current += 1;
                    }
                }

                // If there are no possible numbers, backtracking occurs from
                // the points i and j where mostConstrained returns false below
                if (current == 0) {
                    row = i;
                    col = j;
                    return false;
                }

                // If the current spot has fewer possible numbers than the 
                // previous most constrained spot, current becomes the new
                // most constrained spot (smallest).
                if (current < smallest) {
                    smallest = current;
                    row = i;
                    col = j;
                }
            }
        }
    }
    return true;
}

/*############################################################################
  Backtracking moves back to the previously set row and column and removes the
  number there and looks for the next best option to place there. Recursion 
  occurs if it must keep looking for the correct number.
  ###########################################################################*/

void backtracking(size_t & row, size_t & col, char & num, stack st, 
                  sudokuboard & brd) {
    // Sets column to the top element in the stack.
    col = st.top();

    // Pops first element off of the stack.
    st.pop();

    // Sets row to the new top element of the stack.
    row = st.top();

    // Pops next first element off of the stack.
    st.pop();

    // Finds the number at that row/column spot and deletes it.
    char digit = brd.get(row, col);
    brd.remove(row, col);

    // Makes sure 'digit' is less than 9 so that it can increment it, or else
    // it will backtrack again because it no longer has any further options.
    if (digit < '9') {
        for (char updated = digit + 1; updated <= '9'; updated++) {
            if (brd.canPlace(row, col, updated)) {
                // Places the updated number in the spot and adds the row and
                // column to the stack.
                brd.place(row, col, updated);
                st.push(row);
                st.push(col);
                return;
            }
        }
        backtracking(row, col, num, st, brd);
    }
    else
        backtracking(row, col, num, st, brd);
    
}

/*#############################################################################
  This function loops as many times as needed until the board is solved. It
  first finds if a spot on the board is the most constrained spot on the board
  and sets it if it finds an appropriate number, and if not, it initiates the
  backtracking until mostConstrained returns true.
  ###########################################################################*/

void solve_board(size_t row, size_t col, char num, stack st, sudokuboard & 
                 brd) {
    while (not brd.solved()) {
        if (mostConstrained(brd, row, col, num)) {

            // Uses the find_low function to find the first instance in which
            // a number can fit into a position and changes num accordingly.
            num = find_low(brd, row, col, num);

            // The value is placed on the board, and the row and column are 
            // added to the stack.
            brd.place(row, col, num);
            st.push(row);
            st.push(col);
        }

        else {
            // Backtracking is initiated if mostConstrained returns false.
            backtracking(row, col, num, st, brd);
            
        }
    }
}

int main() {
    sudokuboard brd;
    stack st;
    size_t row = 0;
    size_t col = 0;
    char num = '0';
    char pos;

    // Goes through the input file and replaces each position on the board
    // with the characters in the input file.
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            cin >> pos;
            brd.place(i, j, pos);
        }
    }

    // Calls function to begin solving the board.
    solve_board(row, col, num, st, brd);
    
    // Prints the final result of the board.
    brd.print();
    return 0;
}