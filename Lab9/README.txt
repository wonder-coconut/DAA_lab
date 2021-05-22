RISHAB RAMANATHAN
19XJ1A0558
CSE 2

1.  matrixchain.c

Dynamic programming approach by storing values of subproblems for future use
Compilation:    gcc matrixchain.c -o mc
Execution:     ./mc <array of dimensions>

Inputs are seperated by spaces

Methods:

int chaincalc():
    recursive function to calculate the table of values

void printsequence():
    recursive function to print the chain of sequence

2.  lcs.c

Compilation:    gcc lcs.c -o lcs
Execution:     ./lcs <length of first string> <length of second string> <string1> <string2>

Dynamic programming approach to solving the problem by memoization

Methods:

int lcsdriver():
    initializes the matrix with frequency of matching strings, and printing the longest subsequence through the
    final element pattern
