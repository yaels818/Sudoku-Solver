/*Soduko Solver (using a backtracking algorithm)
------------------------------------------------
Author: yaels818
DOC: 17/09/2023

Notes:
    1. Default board size is 3X3. 
        You can change it using the SIZE variable and it would work 
        for a 2X2 or any other size you might want.
    
    2. User can input any (solvable) Sudoku board, example format is documented 
        in the input_into_board function.
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int const SIZE = 9;
int const ROOT_SIZE = sqrt(SIZE);

int input_into_board(vector<vector<int>> *board){
    /*
        Get input board from user, check that it's valid, then push into our board.

        Parameters:
            vector<vector<int>> *board = pointer to our board

        Input example formats:

            Input 1 - 3x3
                0 4 0 1 0 0 0 5 0
                1 0 7 0 0 3 9 6 0
                5 2 0 0 0 8 0 0 0
                0 0 0 0 0 0 0 1 7
                0 0 0 9 0 6 8 0 0
                8 0 3 0 5 0 6 2 0
                0 9 0 0 6 0 5 4 3
                6 0 0 0 8 0 7 0 0
                2 5 0 0 9 7 1 0 0

            Input 2 - 2x2
                0 1 3 2 
                0 0 0 0 
                0 4 0 1 
                0 0 0 0
        
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
            [row,col] position of the next empty cell (with the digit 0)
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

bool is_digit_valid_in_pos(vector<vector<int>> *board, int digit, int* pos){
    /*
        Check if placing the digit on board in position pos creates conflicts within
        the row, the column, or the box (square). 

        Parameters:
            vector<vector<int>> *board  = pointer to our board
            int digit                   = the digit we just placed
            int* pos                    = the position for said digit ([row,col])

        Return:
            false = if the digit we just placed is clashing with another
            true = if the digit is valid and creates no conflicts in this pos
    */

    // check if valid within row:
    //---------------------------
    // for every col
    for (int i = 0; i < SIZE; i++)
    {
        // if this is the position we just inserted the new digit into - don't check it
        // if it's any other pos on that row - check if it clashes with the digit we placed
        if ((pos[1] != i) && ((*board)[pos[0]][i] == digit))
            return false;   
    }

    // check if valid within col:
    //---------------------------
    // for every row
    for (int i = 0; i < SIZE; i++)
    {
        // if this is the position we just inserted the new digit into - don't check it
        // if it's any other pos on that col - check if it clashes with the digit we placed
        if (((pos[0] != i) && (*board)[i][pos[1]] == digit))
            return false;
    }

    // check if valid within box:
    //---------------------------
    /*
        Example: 
            Say our empty pos is [0,2] ==> box_x = 2/3 = 0, box_y = 0/3 = 0
            ==> our box is the top left, (x,y) = (0,0)

            Say our empty pos is [3,4] ==>
            ==> our box is exactly in the middle, (x,y) = (1,1)

            Say our empty pos is [7,7] ==> 
            ==> our box is the bottom right, (x,y) = (2,2)

        3 4 0 | 1 0 0 | 0 5 0
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
    // find the box matching the new digit's position
    int box_x = pos[1] / ROOT_SIZE;
    int box_y = pos[0] / ROOT_SIZE;

    // for every row from the beginning of the box until the end
    for (int i = box_y * ROOT_SIZE; i < box_y * ROOT_SIZE + ROOT_SIZE; i++)
    {
        // for every col from the beginning of the box until the end
        for (int j = box_x * ROOT_SIZE; j < box_x * ROOT_SIZE + ROOT_SIZE; j++)
        {
            // if there is another digit clashing with our digit
            // AND it's not our new digit
            if (((*board)[i][j] == digit) && (i != pos[0]) && (j != pos[1]))
                return false;
        }
    }

    // no clashes were found
    return true;
}

bool solve_board(vector<vector<int>> *board){
    /*
        Implement the following algorithm to solve the board (if solvable).
        
        The Algorithm:

            Starting with an incomplete board:

            1.  Find the next empty cell.
            
            2.  Attempt to place one of the digits 1-SIZE in that cell.
            
            3.  Check if that digit is valid in the current cell based on the current board
                (check if there are any conflicts within the row, col or box).

            4.  a. If the digit is valid, recursively attempt to fill the board using steps 1-3. 
                b. If it is not valid, reset the cell you just filled and go back to the previous step.
            
            5.  Once the board is full, by the definition of this algorithm, 
                we have found a valid solution (all digits have been checked and found to be valid).
        
        Parameters:
            vector<vector<int>> *board  = pointer to our board

        Return:
            false = if the board is not solved
            true = if the board is solved
    */
    
    // find the next empty cell
    int* empty_cell_pos = find_empty_cell(board);
    int row = empty_cell_pos[0];
    int col = empty_cell_pos[1];

    // if there is no empty cell in the board 
    // (board is full, no clashes ==> solved!)
    if ((row == -1) && (col == -1))
    {
        // free dynamically allocated memory
        free(empty_cell_pos);
        return true;
    }

    // for each possible digit for the board
    for (int i = 1; i < SIZE + 1; i++)
    {
        // if the digit creates no conflict on the board in this cell
        if (is_digit_valid_in_pos(board, i, empty_cell_pos))
        {
            // place the digit
            (*board)[row][col] = i;

            // if you managed to keep solving and all digits were valid
            // --> board is solved, digit placement was indeed correct
            if (solve_board(board))
            {
                free(empty_cell_pos);
                return true;
            }

            // if not - digit placement was incorrect, reset the cell and backtrack
            (*board)[row][col] = 0;
        }
    }

    free(empty_cell_pos);
    return false;
}

int main () {
    // create the sodoku board and a pointer to it
    vector<vector<int>> board(SIZE);
    vector<vector<int>> *p_board = &board;
    
    // if input board is valid
    if (input_into_board(p_board) == 0)
    {
        // print input board
        print_board(board);

        // solve given board (if solvable)
        solve_board(p_board);

        // print output board
        cout << endl << "___ YOUR SOLVED BOARD: ___" << endl << endl;
        print_board(board);

    }

}
