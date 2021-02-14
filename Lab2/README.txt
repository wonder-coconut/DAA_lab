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
1 - Merge sort
2 - Quick sort

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

void printList():
function to print the struct array contents to the terminal. only for debugging.

void printListFile():
identical to the previous function, except it writes to an output file instead of the terminal.

int checkSort():
checks whether the array sorting is succesful or not. Takes field input, only for debugging.

void merge():
function two merge two arrays in a sorted fashion. The function takes in indices for the array limits, divides the array into halves, and continuously
adds elements of both arrays, adding the smallest element first in order. 

void mergeSort():
recursive function to implement the merge sort algorithm. The function divides the array into two, recursively calls itself to sort the arrays, and
calls the merge function to merge it into the final sorted array.

int partition():
initially this method was implemented with the left, right pointer with a pivot element algorithm, which was explained in class. Unfortunately, due
to either an error in my implementation, or the algorithm in general, the code failed to sort for Name fields.
I ended up using an alternate partition algorithm, without an initial pivot, explained below:
    -assign left and right pointers to the array under consideration
    -the increment of the left and right pointers are switched everytime a swap occurs. For example:
    assume left pointer is incrementing first. If swap occurs between left and right pointers, switch from increment of left pointer to decrementing right
    pointer, and vice versa. This switch will occur everytime a swap occurs.
    -compare the elements at the left and right pointers
    -if left is greater than right, swap. Then switch the pointer increment/decrementing
    -finally, increment/decrement the left/right pointers, depending on current state of array.
    -repeat the steps until the left and right pointers are equal to each other.
    -return the left/right pointer value as the partition variable. By theory, the element at the pointer becomes the pivot.

The switch is implemented by using a flag variable which is incremented everytime a swap occurs. The modulus of this variable with 2 gives us a
binary output of 0 or 1, which respectively decides which pointer variable to alter.

void quickSort():
function to implement quickSort algorithm. The function gets the partition index from the partition() function, divides the array into its respective
subarrays and recursively sorts(calls quickSort) the two subarrays.

void main():
driver function for the program.
