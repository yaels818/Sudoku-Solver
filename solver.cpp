/*Soduko Solver (using a backtracking algorithm)
------------------------------------------------
Author: yaels818
DOC: 17/09/2023

Notes:
    1. Default board size is 3X3. 
        You can change it using the SIZE and ROOT_SIZE constant variables
        and it would work for a 4X4 or any other size you might want.
    
    2. User can input any (solvable) Sudoku board, example format is documnented 
        in the input_into_board function.

The Algorithm:
    
    Starting with an incomplete board:

    1.  Find the next empty cell.
    
    2.  Attempt to place one of the digits 1-SIZE in that cell.
    
    3.  Check if that digit is valid in the current cell based on the current board
        (check if there are any collisions within the row, col or box).

    4.  a. If the digit is valid, recursively attempt to fill the board using steps 1-3. 
        b. If it is not valid, reset the cell you just filled and go back to the previous step.
    
    5.  Once the board is full, by the definition of this algorithm, 
        we have found a valid solution (all digits have been checked and found to be valid).

*/

#include <iostream>
#include <vector>
using namespace std;

int const SIZE = 9;
int const ROOT_SIZE = 3;

int input_into_board(vector<vector<int>> *board){
    /*
        Get input board from user, check that it's valid, then push into our board.

        Parameters:
            vector<vector<int>> *board = pointer to our board

        Input example format:
            0 4 0 1 0 0 0 5 0
            1 0 7 0 0 3 9 6 0
            5 2 0 0 0 8 0 0 0
            0 0 0 0 0 0 0 1 7
            0 0 0 9 0 6 8 0 0
            8 0 3 0 5 0 6 2 0
            0 9 0 0 6 0 5 4 3
            6 0 0 0 8 0 7 0 0
            2 5 0 0 9 7 1 0 0
        
        Return:
            0 if all input cells are valid (within board's size)
            -1 if not
    */
    
    // for every row in the board
    for (int i = 0; i < SIZE; i++)
    {
        // for every cell in the row
        for (int j = 0; j < SIZE; j++)
        {
            // get input number from user
            int input;
            cin >> input;

            // if input is within the board's size, push into cell
            if (input >= 0 && input <= SIZE)
                (*board)[i].push_back(input);
            else
            {
                cout << "ERROR: numbers on the board are not within its size." << endl;
                return -1;
            }
        }
    }

    cout << endl;
    return 0;
}

void print_board(vector<vector<int>> board){
    /*
        Print our board.

        Parameters:
            vector<vector<int>> board = copy of our board

        Print example format:
            0 4 0 | 1 0 0 | 0 5 0
            1 0 7 | 0 0 3 | 9 6 0
            5 2 0 | 0 0 8 | 0 0 0
            - - - - - - - - - - -
            0 0 0 | 0 0 0 | 0 1 7
            0 0 0 | 9 0 6 | 8 0 0
            8 0 3 | 0 5 0 | 6 2 0
            - - - - - - - - - - -
            0 9 0 | 0 6 0 | 5 4 3
            6 0 0 | 0 8 0 | 7 0 0
            2 5 0 | 0 9 7 | 1 0 0

    */

    // for every row in the board
    for (int i = 0; i < SIZE; i++)
    {
        // print for every ROOT_SIZE row
        if (i % ROOT_SIZE == 0 && i != 0)
            cout << "- - - - - - - - - - -" << endl;

        // for every cell in the row
        for (int j = 0; j < SIZE; j++)
        {
            // print for every ROOT_SIZE col
            if (j % ROOT_SIZE == 0 && j != 0)
                cout << "| ";

            // for every last col
            if (j == SIZE-1)
                cout << board[i][j];

            // for every non-last col
            else
                cout << board[i][j] << " ";
        }
        
        cout << endl;
    }
}

int* find_empty_cell(vector<vector<int>> *board){
    /*
        Find the next empty cell.

        Parameters:
            vector<vector<int>> *board = pointer to our board

        Return:
            [i,j] position of the next empty cell (with the digit 0)
            [-1,-1] if board is full

    */

    // create a new dynamically allocated array [-1,-1] 
    int* pos = new int[2];
    pos[0] = -1;
    pos[1] = -1;
    
    // for every row in board
    for (int i = 0; i < SIZE; i++)
    {
        // for every cell in row
        for (int j = 0; j < SIZE; j++)
        {
            // if cell is empty
            if ((*board)[i][j] == 0)
            {
                // store cell position in the array and return it
                pos[0] = i;
                pos[1] = j;

                return pos;
            }
        }
    }

    // if no empty cells were found, return [-1,-1]
    return pos;
}

int main () {
    // create the sodoku board and a pointer to it
    vector<vector<int>> board(SIZE);
    vector<vector<int>> *p_board = &board;
    
    if (input_into_board(p_board) == 0)
    {
        print_board(board);
        int* empty_pos = find_empty_cell(p_board);
        
        cout << "[" << empty_pos[0] << "] [" << empty_pos[1] << "]" << endl;

        // free dynamically allocated memory
        free(empty_pos);

    }

}
