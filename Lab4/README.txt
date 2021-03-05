RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46

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

