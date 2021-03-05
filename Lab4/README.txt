RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46


The folder is divided into two programs, one for tree sort and the other for block matrix multiplication.

1) Tree sort

Compilation: gcc treeSort.c -o ts

Input parameters: ./ts {omit the < ./ > on cmd}

As a whole, this program takes an input from the file "DAALab_Input1.txt", takes in user input from the user for choice of field and algorithm,
and writes the output into the file "DAALab_Output1.txt". Note: the code is implemented in a manner where the input file must be in the same directory
as the source code, as the address specified points to the same directory. Furthermore, since the program appends to a file instead of writing from 
scratch, the output file will have to be wiped/deleted for a fresh new output, or the next output will just be appeneded to the first output.
 
The program employs use of various functions and structures, as explained below:
(further precise working is explained by comments in source code)

struct team:
a predefined structure with variables to store the roll number, name and team number. A struct team element represents a single person and their
details.

struct node:
a predefined structure to represent the binary search tree node in C. It's mapped using the variables for data, and the addresses to the left and
right subtrees.

int rollConvert():
since only the last two digits of a roll number are unique, this splits the last two digits from the string, for easy manipulation and sorting.

void input():
function to copy data into a struct team array from the input file.

void equate():
function to equate the first team element(destination) to the second(source), called by reference.

void appendElementFile():
function to append a struct element to the output file, using the 'a' file parameter.

struct node* newNode():
function to dynamically create a new struct variable of type 'node', initialize it with the values passed in formal parameter 'struct team teamset'
and initialize left and right subtrees to NULL (leaf node). It returns the created node's address

void insert():
recursive function that takes in the pointer to the root node, and the data (struct team teamset), to insert a new node according to the BST structure.
If the root node is NULL (leaf node), the data is inserted at that position. If not, the function recursively calls the insert function, for either the
left or right subtree, depending on whether the teamset data is more or less than the root.

void inorder():
recursive function to print the inorder representation of the BST.

void inorderWrite():
identical to previous function, except it writes to the output file instead of printing to terminal.

void main():
driver function for the program.

2) Block Matrix multiplication

Compilation: gcc blockMulti.c -o bm

Execution: ./bm <block length> {omit the < ./ > on cmd}

This program attempts to multiply two 1024 * 1024 matrices, and prints the runtime for it. Output is not written to any file, but the runtime has been
analyzed and plotted in the same root folder.

Attached in the same folder is the plot.png, which maps the runtime for different values of blocksize (4,8,16,32,64)

Given below are the function and members uses applied in the script:

int len, int bl:
global variables used to store the value of the length and block length dimensions of the matrix

int initialize():
function to initialize the parameter array elements. The function assigns a pseudo-random value to each element, the random value being within a specified
range in the function parameter.

void blockMultiplier():
function to implement block matrix multiplication for the input matrices.
The function achieves this by dividing the iteration in two parts:
-block iteration
-element iteration within the block

The outer three loops are used to iterate through the blocks of the matrix, this is achieved by incrementing each index by the block length.
The inner three loops are used to iterate through the elements within the current block.
The i and j indices represent the coordinates of the element/block in the final result matrix, into which the multiplication result is assigned.
The k index serves as an iterator to parse throught the rows/columns of the first and the second matrix respectively.

void printArray():
function to print each element of the input matrix. Only for utility, not used for final output, highly complex for larger matrices.

int main():
driver function for the script.
significant aspects:
-the matrix had to be dynamically initialized due to the large size of elements required, using malloc()
-gettimeofday() function was used to log the runtime of various aspects of the program.
