/******************************************************************************
 * sudokuboard.h                                                              *
 *                                                                            *
 * Completed by:  Oliver Keh                                                  *
 *                                                                            *
 * February 26, 2016                                                          *
 *                                                                            *
 * The header file contains the sudokuboard class and defines whether         *
 * functions in the class are declared as public or private.                  *                                         
 *                                                                            *
 *****************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

class sudokuboard {

    public:
        sudokuboard();
    	void place(size_t r, size_t c, char n); // place numeral n at position 
                                                // (r,c)
    	void print() const; // write the board to cout
    	char get(size_t r, size_t c) const;// return the numeral at position
                                           // (r, c)
    	void remove(size_t r, size_t c); // remove the numeral at position 
                                         // (r, c)
    	bool canPlace(size_t r, size_t c, char n) const; // true if he board 
                                                         // would allow placing
    							                         // n at (r, c)
    	bool solved() const; // true if there are no blank spots on the board

    private:

    	string size_board[9];
        size_t size;

};