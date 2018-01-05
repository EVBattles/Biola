/*

// Time worked

// 11/15 2:00 PM - 6:00 PM : Step One and Part of Step Two
// 11/16 10:00 PM - 1:00 PM : Step Two through Print
//       3:00 PM - 4:00 PM : Debugging


Instructions

Write a program in VS C++2017 which generates a one - state extended pushdown machine using the rules 
of a simple grammar provided by the user.The pushdown machine determined is then printed to the screen 
in a 2 - dimensional array fashion.Your program should first ask the user to provide information for the 
grammar from which the pushdown machine is generated.Let's assume all nonterminals are represented in 
capital letters and all terminals are represented in lowercase letters. The following shows an example 
demonstrating how rules of a simple grammar can be entered, where user's inputs are represented in boldface


Reubric

(3.1) Each test case shares equal points. For example, if two test cases are used to test your program, 
then each test case is allocated 2.5 points.(3.2) Each entry in the one-state extended pushdown machine for 
a test case shares equal points. For example, since there are 15 entries in the pushdown machine shown on 
page 1 for the sample run and the test case is allocated 2.5 points, each entry is worth 0.17 point.


In Class Notes

Create a 1 state extended pushdown machine for simple grammar
Step 1: build a table with each column labled by a terminal symbol and each row labeled by a nonterminal
or terminal symbol
Step 2: for each grammar rule of the form A->a&, fill in the cell in row A and column a with "rep(&a), retain"
Step 3: fill in the cell in row a and column a with "pop, advance" for each terminal symbol a
Step 4: fill in the cell in "bottom marker" and column "end marker" with accept
Step 5: fill in all the other entries with reject
Assume the first letter is terminal
Use a 2D array
Column = # of toatal variables (nonterm and term) + bottom of stack
Row = # of term + end of line
Output: One state extended pushdown machine -> ask for rules and create the table
NOTE: No error check required (can assume test example is correct)
*/