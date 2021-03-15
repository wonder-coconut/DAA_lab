RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46

The folder is divided into 2 folders, one normal and one bonus.

Normal:

I]  defective_chessboard.c

Compilation:    gcc defective_chessboard.c -o chess
Execution:      ./chess <board length> <defective row coordinate> <defective column coordinate> <print flag> <colour flag>

Note: This program involves colour output alteration (for better visualization of triominoes), but the code will only work
on linux systems.

This program fills up a defective chessboard(one invalid tile) with triominoes.
Logic: The board is divided into 4 quadrants. If one quadrant contains the defective tile, the corners facing the midpoint of
the board, of the remaining three quadrants, will be filled as a triomino. This triomino is in turn treated as a defective tile
and the algorithm is applied recursively to the four individual quadrants. The base case occurs when the size of the board is
equal to 1, which is when the program terminates.

This code was achieved by the following functions and global variables:

int len, drow, dcol, tileNum:
length,defective row coordinate, defective column coordinate and tile number respectively. Tile
number tracks the unique triomino being assigned.

int *board:
pointer to array storing the representation of the defective chess board

void black()...reset():
functions to change the colour of the terminal output

void colour():
driver function for colour

double timeconvert():
function to convert seperate seconds and microseconds into a single seconds variable

void printBoard():
function to print the defective chessboard

void fillBoard():
function to fill the board with triominoes.
The function takes in 'row' and 'col', which represent the leftmost row and topmost column of the board under consideration.
'defRow' and 'defCol' are the defective tiles of the board under specification (which may vary depending on the algorithm as
aforementioned). Lastly, 'size' specifies the dimensions of the board under specification.
