# Linked List Implementation 
###### CS 162 - Winter 2020 at Oregon State University

## Description 

Welcome to C++ Linked list implementation. In this program, you'll be able to
store integers into a linked list. The program would be able to sort the Linked
list in either ascending or descending mode. After that, the program will print
out the sorted linked list, and tell you the total amount of prime numbers
found within the linked list!

## Instructions 
1. Compile your program with 
	```make```
2. Run the program with 
	```./project```
3. You start by inputting the first value in the linked list:

		Please enter a number:
		90

	 Your linked list would look something like this:
	 `90`


## Functionalities of The Program 

1. Add more members to the linked list
	
	###### Prompting User to Answer Y/N
	- After the first value has been stored in the linked list, the program
	will ask whether or not you want to input another value.

			Do you want to input another num(y or n) :

	- If you write Y or y, the program will prompt you to enter another value. If you write N or n, the program will lead you to the next part of the
	program (Step 2).
	
	###### Ask User About Index 

	Afterwards, You will be given two options: 

	Choose the following: 
	
			(1)  Add member without index. 
			(2)  Add member with index. 

	- If you choose 1, you will be prompted to enter a value, and the push_back() function will be run. 
	- If you choose 2, you will be prompted to enter a value and index on which you want
	to insert your value. Insert() function will run.

	**NOTE** : 
	    If you enter an index that is out of bounds, the program will prompt you to 
	    enter another value.

	Range requirements:
	- As the values of the linked list are stored as ints, the value you
	enter shouldn't be less than -2147483646 or more than 2147483646. If the
	value you entered is out of the range, the program will tell you that
	value isn't valid and prompt you to enter another value.


2. Sort ascending or descending

	 The program will ask you whether you want the linked list to be sorted ascending or descending.

		 Sort ascending or descending (a or d):

	 - If you enter A or a, the program will call a recursive merge sort to sort the linked list ascending.
	 - If you enter D or d, the program will call a recursive selection sort to sort the linked list descending.

3. Print sorted linked list

	Your linked list values will be printed to the screen, after being sorted based on the option you chose.

4. Print the total of prime numbers

	The program will print out the total of prime numbers found within the linked list.

5. Play again?

	After printing out information regarding the linked list, the program will ask whether you want to play again.

			Do you want to do this again (y or n)?

	- If you enter Y or y, the program will start from the beginning.
	- If you enter N or n, the program will quit. Hope you enjoyed playing!


## Limitations

 1. This program assumes that the user won't enter a string when asked to enter
    the value (which is type int) to be stored in node. 
