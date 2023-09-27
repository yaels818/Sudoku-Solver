# Sudoku Solver (using a backtracking algorithm)
## Sudoku Solver 
Having trouble finishing your sudoku board? Want to check your solution before the next newspaper issue comes out?

**Problem solved!**

Just give this C++ Sudoku Solver your board in a format similar to the examples - ANY board, 9x9 or even 16x16 - and if the board is solvable, you will have the solution in just a few seconds!

## Why Backtracking?
Because the Naive approach would require us to generate an exponential amount of all possible placements for the board, and check the validity of each possible board, one by one, to exclude all but the single right board that would be the solution.

**That's a lot of work.** Sure, it's the computer that does all the heavylifting, but still - why waste all this time and effort?

Backtracking makes the coding a bit more complex, but it also makes life easier.

## How The Backtracking Thing Works?
1. **Our Choice:** The input board you give to the program will have some digits in it other than zero. Those digits we won't do anything about, they are part of the solution, not the problem.
   <br> The cells with zeroes, however, those are the empty cells we need to fill. We would have to place numbers between 1 and x, with x being the board's size.
   <br> So, for example, if our board is a standard 9x9, we would have to place 1-9 in each empty cell.

2. **Our Constraints:** Our placements can't "break" the board, meaning there can't be any matching digits within the same row, column, or sub-grid.
   <br> Here's where the magic of backtracking/recursion comes to play:
   <br> Every placement we made up to this point is valid. Why?
   <br> **Because we only move forward if our placement didn't break the board.**
   <br> That means that by the time we get to the last cell of the board we KNOW we reached the solution, and that it's valid - because all placements before this cell were valid.

4. **Our Goal:** Fill the board!

## Screenshots of This Solver in Action
### Against a baby 4x4 board:

![Screenshot from 2023-09-19 01-58-30](https://github.com/yaels818/Sudoku-Solver/assets/99403939/b91eeedf-f751-4251-8435-860a49826d4e)

### Against a normal 9x9 board:

![Screenshot from 2023-09-19 01-42-13](https://github.com/yaels818/Sudoku-Solver/assets/99403939/a9c5248e-6c93-40a3-9314-17a2dbaebac4)

### Against an expert 16x16 board:

![Screenshot from 2023-09-22 22-01-20](https://github.com/yaels818/Sudoku-Solver/assets/99403939/8a281552-b2db-46bd-9964-50f98d435757)


