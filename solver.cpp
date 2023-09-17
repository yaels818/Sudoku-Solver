/*Soduko Solver (using a backtracking algorithm)
------------------------------------------------
Author: yaels818
DOC: 17/09/2023
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

int main () {
    // create the sodoku board and a pointer to it
    vector<vector<int>> board(SIZE);
    vector<vector<int>> *p_board = &board;
    
    if (input_into_board(p_board) == 0)
    {
        print_board(board);
    }

}
