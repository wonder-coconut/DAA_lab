RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46

Both questions of the lab are implemented in the single source code "sorting.c"

Compilation: gcc sorting.c -o sort

Input parameters: ./sort <choice for field of sorting> <choice for algorithm of sorting>

Field parameters: 
1  - Roll Number
2  - Team Number
3  - Name
-1 - Field priority order (team number, roll number, name)

algorithm parameters:
1 - Insertion sort
2 - Selection sort

As a whole, this program takes an input from the file "DAALab_Input1.txt", takes in user input from the user for choice of field and algorithm,
and writes the output into the file "DAALab_Output1.txt". Note: the code is implemented in a manner where the input file must be in the same directory
as the source code, as the address specified points to the same directory. 
The program employs use of various functions and structures, as explained below:
(further precise working is explained by comments in source code)

struct team:
a predefined structure with variables to store the roll number, name and team number. A struct team element represents a single person and their
details.

int rollConvert():
since only the last two digits of a roll number are unique, this splits the last two digits from the string, for easy manipulation and sorting.

void input():
function to copy data into a struct team array from the input file.

void swap():
function to swap two struct team elements, changes are relayed without returning as parameters are transferred by reference(pointers).

void equate():
function to equate the first team element(destination) to the second(source), called by reference.

void selectionSort():
function to implement the Selection Sort algorithm, with a choice for field of sorting, called by reference.
The function contains an if-else ladder to differentiate between the field parameters. If the field parameter is -1,
the code will sort according to the specified priority of the fields, which kicks in when there's a kind of stalemate
(two equal fields) between two elements. In case of a stalemate, the control goes to comparing the next priority field, until
either the stalemate is resolved or all fields are exhausted, in which case the elements will be sorted according to their input order.

The stalemate checks occur during the search for the minimum element during each iteration.

void insertionSort():
identical to the previous function, except for the Insertion Sort algorithm, and the stalemate checks occur while checking for position of insertion.

void printList():
function to print the struct array contents to the terminal. only for debugging.

void printList():
identical to the previous function, except it writes to an output file instead of the terminal.