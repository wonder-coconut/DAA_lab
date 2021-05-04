RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46

The folder is divided into 2 subfolders, one normal and one bonus.

Normal:

I]  defective_chessboard.c

Compilation:    gcc defective_chessboard.c -o chess
Execution:      ./chess <board dimension> <defective row coordinate> <defective column coordinate> <print flag> <colour flag>

Where:
Print flag: choice for printing output. 1 for yes, 0 for no
Colour flag: same as print flag, choice for coloured triominoes

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
Base case is when size is one, when the program is terminated.
As mentioned in the logic before, this program places a triomino in the center of the board and treats it as a defective tile.
Each if-else block is for each quadrant of the board, checking for existence of defective tile in it. If defective tile is
found, recursively call fillBoard for that quadrant. Else, fill the opposite corner as a triomino tile.

int main():
driver function, logs runtime using gettimeofday()

II] strassen.c

Compilation:    gcc strassen.c -o strassen
Execution:      ./strassen <matrix dimension> <print flag>

Where:
Print flag: choice for printing output, 1 for yes and 0 for no

This program attempts to execute strassen's multiplication for an input matrix. Initially, the script was designed such that
the algorithm was executed completely recursively. But practically, the runtime for this script goes extremely large, with some
estimates for a 1024 * 1024 matrix reaching 40 minutes. I suspect it's partly due to the extremely large recursion tree born as a result
of a >= 1024 matrix, coupled with the large submatrices needed at each function call.

Therefore, this script employs a mixed iterative-recursive approach.

For matrices with a size lesser than 512 * 512, the code resorts to the naive approach of simple matrix multiplication.
For larger matrices, strassens matrix multiplication is applied recursively until the submatrix size reaches the base case of
512 * 512

This code was achieved by use of the following methods and global variables:

int len:
stores the dimension of the matrices.

double timeconvert():
utility function to format the runtime into a single floating point seconds variable.

void initialize():
function to randomize the elements of the matrices.

int * add() / int * subtract():
function to arithmetically add/subtract two input matrices, and return their address. This will be used in the strassen's equations.

void multiply():
naive approach to matrix multiplication, used for smaller matrices (dimension <= 512)

int * strassenMultiply():
primary recursive function to execute strassen's equations.

The base case is for size <= 512 , where the code falls back to the naive approach to matrix multiplication. A large number as 512 was chosen
to curb the recursion, since a larger extent of recursion led to a significantly larger runtime.

The function starts off with creating temporary submatrices for the quadrants of A and B (input matrices). These submatrices are used for
calculating the M1-7 matrices, recursively calling strassenMultiply() wherever multiplication is required.

Once these submatrices are created, the M1-7 matrices are used to create the quadrants of the resultant matrix C, using strassen's equations.
These quadrants are combined into the final resultant matrix, which is then returned as output.

void printArray():
utility function to print a matrix

int main():
driver function for the program, runtime calculated by gettimeofday. The runtime is logged into a file called "TimeLogDc.txt"

BONUS QUESTIONS:

I] ith_smallest_number.c

Compilation:    gcc ith_smallest_number.c -o small
Execution:      ./small <i position> <array of integers>

Where <i position> is the ith smallest number to be found

This program uses quick select algorithm to find the ith smallest number, which is a variation of quicksort algorithm. The primary principle
is that the number used as pivot, after partitioning, will reach it's final sorted position in the array. If that number matches the input
position, that number is the ith smallest number required.
The complexity of this function will average to O(n) time complexity, since the partition function takes O(n) complexity. 

void printArr():
utility function to print the array

void swap():
function to swap arrays using call by reference.

int partition():
partitions the array (within the left and right limits) and returns the pivot element index, where the pivot element value is taken as the
last element of the array.

int quickSelect():
returns the ith smallest element in the array. This is achieved by using partition() to move the pivot to the correct sorted position, then
checks the position with the input i. If equal it returns the value as output, else recursively executes either the left or right partitioned
array, depending on whether i is greater or lesser than the partition position.

int main():
driver function

II] median.c

Compilation:    gcc median.c -o median
Execution:      ./median <array 1> <array 2>

Note: both arrays must be equal length and sorted.

The logic used for computing the median is similar to that of binary search. The median is computed for both arrays, and then compared.
Accordingly, the array is divided into subarrays and recursively executed until median is computed. Further explained in the individual
function description.

void printArray():
utility function to print an array under certain limits.

int checksort():
checks the sorting of the input array.

double median():
returns the median value for any length sorted array.

double medianDriver():
function to calculate the median value for two input sorted arrays.
As aforementioned, the logic is similar to binary search. The median of the two individual arrays are computed and then compared.
    -If the two medians are equal, the value is returned as the median of the combiend list.
    -If the first median is larger than the second, we can infer that the actual median will be behind the current median in the first
    subarray. Conversely, the actual median will be ahead of the current median in the second subarray.
    -If the second median is larger than the first, the converse of the previous statement will be true (actual median is ahead of current
    median in the first subarray, and vice versa for second subarray)

This will recurse until either the median values are equal, or the subarray becomes unit length, at which point the average of the two medians
becomes the final median.

Since this is a divide and conquer algorithm similar to binary search, the time complexity will be O(n).

int main():
driver function