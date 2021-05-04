RISHAB RAMANATHAN
19XJ1A0558
CSE2

This folder is divided into two source code files, for their respective problem statements.

1)reliability.c

Compilation:    gcc reliability.c -o rely -lm
Execution:      ./rely <number of stages> <max cost> <array of costs for each stage device> <array of reliability for each stage device>

The array inputs are delimited by a space : ' '

The logic of the program is explained in the following method descriptions:

int basen():
takes a number input and a base input, and converts the number into the corresponding base input

double reliability():
takes all user inputs. The logic of the function can be broken down into seperate parts:

-Finding the minimum cost. This is achieved by a simple parse of the cost array
-Finding the maximum number of devices in a single stage for all stages. This is computed to define the dimension of the
table matrix used to store the elements(reliability and cost) of combination of all the stages and combination of devices.
Rough Table matrix format:
                    1 parallel device       2 parallel devices      3 parallel devices ....
max parallels for s1        -                       -                       -
max parallels for s2        -                       -                       -
max parallels for s3        -                       -                       -
    .
    .
    .
Both values of cost and reliability are stored to make the program more time efficient, as computing the most reliable
output may involve exponentially large number of cases.
-Finding the optimal device combination.
This is done by parsing through every possible combination of devices and finding the combination with maximum reliability
under the given constraint.
Traditionally, finding these kind of combinations might require a predefine set of loops to parse through each row of the
matrix to generate every combination possible. This is impossible when the dimensions of the array are user defined,
and not known before hand.

Therefore, I came up with a certain workaround, which I will explain ahead.

The objective was to parse through the matrix in such a method that each row has to be parsed for each element of the 
previous row.
To make things clearer, here's an example:

For matrix[ a   b   c
            d   e   f
            g   h   i ]

g , h , i would have to be accessed for every access of d and subsequent access of e
Similarly d , e , f would be accessed for every a and b.

This would generate a pattern similar to

a,d,g
a,d,h
a,d,i
a,e,g
.
.
.

c,f,i
Which is the set of combinations we need.
After looking at patterns in the counters for each row, this resembled the progression of a number with the base of 
the number of columns in the matrix. In the above example, that would be base 3
Thus the index progression would be:
000
001
002
010
011
012
.
.
.

222
The total number of combinations would thus be the maximum value for those number of digits, which would be r^c
rows and columns respectively.
Therefore these numbers could then be mapped to the matrix element to acquire each combination we require.
Since the number of columns/could exceed 10, using a single number to store this value might fail for bases > 10.
Therefore, the number is represented in an array of n bytes, where n is the number of rows of the matrix.
Those combinations could then be computed on to find the maximum reliability value under the max cost, which would yield
us the result.