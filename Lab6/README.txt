The problem statements are implemented in seperate scripts. Both programs use the greedy approach, as explained further.

I] knapsack.c

Compilation:    gcc knapsack.c -o knapsack
Execution:      ./knapsack <number of objects> <array of object profits> <array of object weights> <knapsack weight limit>

all array elements are space seperated values in input

This program uses the greedy approach, by choosing the most profitable object for its weight. This is achieved by first creating a profit/weight
array , then choosing the maximum element of that array at each iteration , until either the knapsack is full or the objects are exhausted.

This is implemented in the function knapsack():

knapsack():
Takes in profit, weight and profit/weight arrays as input. The function loops until either the knapsack is full or the objects are exhausted.
Within the loop:
    The function gets the index of the maximum profitable object, and then subsequently deletes that object, for an exhaustive list. The function
    adds the whole object weight, if there is enough space, else adds a maximum fraction of the object, to completely fill the knapsack, and
    then exits the function.

II] jobSequence.c

Compilation:    gcc jobSequence.c -o job
Execution:      ./job <number of jobs> <array of job profits> <array of job deadlines>

all array elements are space seperated values in input

The greedy approach here is to choose the most profitable job possible at a moment, and then check if it fits the existing deadline, without
disrupting the current timeline of jobs. This is explained in depth in the function description of sequencer():

sequencer():
The function takes in the profit and deadline arrays as inputs. It gets the max deadline by choosing the max value from the dealine array,
and creates a timeline array using the max deadline. A variable is made to check for how many spots are filled in the timeline is available.
Once this value hits zero, the function stops.

In the loop:
    a job variable stores the maximum profit job index at that iteration. The function then iterates from the latest possible deadline for 
    specific job, and goes earlier in the timeline by 1 unit, until a free spot is available.
    If the spot is available, it is filled by the job under consideration, else the job is discarded. This runs until the timeline is filled, or
    the number of jobs are exhausted.


Common convenience functions:

printArrayInt():
Prints an integer array

printArrayFloat():
prints a floating point number array

int maximum():
returns the index of the maximum element, with a choice of deletion of the max element

int min():
returns the minimum of two inputs

int main():
driver function