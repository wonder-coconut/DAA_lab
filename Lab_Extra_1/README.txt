The 3 problem statements are executed in seperate scripts

1]meetings.c

Compilation:    gcc meetings -o meeting
Execution:      ./meeting <number of meetings> <array of start times> <array of end times>

All array elements are divided by a space, during input

Any uses of the variable 'n' refers to the <number of meetings>

The approach to this problem is characteristic of the greedy approach. First, the meetings are sorted by the finish time field (ascending).
Once the meetings are sorted, they're added sequentially to the final answer if they fit the constraints:
-The first meeting is taken as the first element of the array
-For every next meeting, if the next meeting starts after the finish time of the previous meeting (they cannot start and finish at the same
time), it's counted as a valid meeting.
-This is done until the last meeting is reached.

These constraints ensure the maximum number of meetings possible to be accomodated in the timeframe.

The time complexity of the meeting counter is O(n) , but since merge sort is implemented to sort the inputs, the time complexity upper bound
reaches O(nlog(n)).
The space complexity is the O(n), owing to the struct array of length n created.

2]password.c

Compilation: gcc password.c -o pass
Execution: ./pass <number of digits> <maximum sum of digits>

Any use of variable 'n' refers to <number of digits>

This program too uses the greedy approach. The logic used is to fill the digits in the sequence of most significant digit to least.
-An integer pass variable stores the password.
-If the current sum is more than 9 (greatest decimal base single digit value), 9 is appended to the pass variable. After this, the sum is 
subtracted by 9.
-If the sum is lesser than 9, the sum is appended to the pass variable, and sum is set to 0
-If sum is 0, a 0 is appeneded to pass.
-This is repeated until all digits are filled.
The principle on why this works is that the maximum variable will always begin with the largest possible digit in the most significant
position.

The time complexity achieved is O(n), since each digit is appended once.
The space complexity achieved is O(1), since (apart from input variables) only a constant number of variables are used to generate the password.

3]stairs.c

Compilation:    gcc stairs.c -o stair
Execution:      ./stair <number of stairs>

Any use of variable 'n' refers to <number of stairs>

This program uses the fibonacci sequence to calculate the number of possible paths. The recurrence relation is:
        paths(n) = paths(n-1) + paths(n-2)

This works because at any moment, you can choose to take 1 step or 2 steps. Thus, the total number of paths would be the sum of their individual
paths. But since programming a fibonacci sequence recursively is inefficient, we'll use the logic of the fibonacci number and compute the
output iteratively, thus achieving the desired time complexity of O(N).

The space complexity is O(1), since 3 (constant) variables are used to calculate the fibonacci number.
