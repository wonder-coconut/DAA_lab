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

void printList():
identical to the previous function, except it writes to an output file instead of the terminal.

void merge():
function two merge two arrays in a sorted fashion. The function takes in indices for the array limits, divides the array into halves, and continuously
adds elements of both arrays, adding the smallest element first in order. 

void mergeSort():
recursive function to implement the merge sort algorithm. The function divides the array into two, recursively calls itself to sort the arrays, and
calls the merge function to merge it into the final sorted array.

int partition():
this function divides the main array into two subarrays: the left array and the right array, with elements lesser than and greater than a specified
pivot value, respectively. The algorithm(in simple language) chosen for the partition process is as follows:
    -The pivot value is chosen from the first element of the array under consideration.
    -Take two pointers from the ends of the array, excluding the pivot element. Name it left and right pointers.
    -Iterate the left pointer through the array until it comes across an element greater than the pivot.
    -Repeat for the right pointer, until an element lesser than the pivot is encountered.
    -Swap these elements, to get them to the proper side of the array w.r.t. pivot.
    -Repeat the previous steps until the left pointer is equal or greater than the right pointer.
    -Swap the pivot element to the partition point, thus making it the permanenet sorted position of the pivot element.
after swapping, this function returns the partition element, so that the quickSort function can divide the array and recursively sort it.

void quickSort():
function to implement quickSort algorithm. The function gets the partition index from the partition() function, divides the array into it's respectively
subarrays and recursively sorts(calls quickSort) the two subarrays.

void main():
driver function for the program.
