RISHAB RAMANATHAN
ROLL:   19XJ1A0558
TEAM:   46

All three questions of the lab are implemented in the single source code "searching.c"

Compilation: gcc searching.c -o search

Input parameters: ./sort <choice for field of sorting> <choice for algorithm of sorting> <search query> {omit the < ./ > on cmd}

Field parameters: 
1  - Roll Number
2  - Team Number
3  - Name

algorithm parameters:
1 - Linear search
2 - Binary search
3 - Fibonacci search

As a whole, this program takes an input from the file "DAALab_Input1.txt", takes in user input from the user for choice of field and algorithm,
and writes the output into the file "DAALab_Output1.txt". Note: the code is implemented in a manner where the input file must be in the same directory
as the source code, as the address specified points to the same directory. Furthermore, since the program appends to a file instead of writing from 
scratch, the output file will have to be wiped/deleted for a fresh new output, or the next output will just be appeneded to the first output.
 
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

void appendElementFile():
function to append a struct element to the output file, using the 'a' file parameter.

void merge():
function two merge two arrays in a sorted fashion. The function takes in indices for the array limits, divides the array into halves, and continuously
adds elements of both arrays, adding the smallest element first in order. 

void mergeSort():
recursive function to implement the merge sort algorithm. The function divides the array into two, recursively calls itself to sort the arrays, and
calls the merge function to merge it into the final sorted array.

void linearSearch():
function to implement the linear search algorithm. It takes a string input for the search term and converts it to the required type as necessary.

void duplicateElement():
function to print the duplicate elements of the search query for the binary and fibonacci searches. The principle is that since the array is sorted,
all duplicate elements of a specific field will be adjacent to each other. The function traverses left and right of the search index given by the
searching function, and outputs until a different element is occured.

int binarySearch():
recursive function to implement binary search, by checking the middle element for the search query. If not found, it will divide the array into 
equal halves and implement binarySearch recursively on the array with the search element, achieved by a comparison between the middle element and 
the search query 

int binaryDriver():
driver function for binary search, sorts the array and calls binarySearch() with the proper parameters. Returns 1 if the search query is found, else
0

int isFibonacci():
checks whether a number is a fibonacci number. It does so by using the property that any fibonacci number will satisfy the condition:
    (5*n^2 + 4) or (5*n^2  - 4) is a perfect square. This is a result of the golden number property, which was born out of the golden ratio.
Source: https://mathlesstraveled.com/2016/03/19/golden-numbers-are-fibonacci/

int fibIndex():
returns the fibonacci division of the array using isFibonacci(). This is done according to the algorithm for fibonacci search, where the division of 
the array is done at the index which is numerically equal to (m-2)th fibonacci number, given that the smallest fibonacci number that is larger than the
length of the array is the (m)th fibonacci number.
This is achieved by finding the smallest fibonacci number larger than or equal to the array length, then dividing it twice by the golden ratio.

int fibSearch():
identical to binarySearch, except the index is not at the mid point, but at the length returned by fibIndex()

int fibonacciDriver():
identical to binaryDriver(), except it implements fibonacci search.

void main():
driver function for the program.

