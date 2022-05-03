# Text Surgeon
###### CS 161 - Winter 2020 at Oregon State University

## Description

Write a program that takes in a user’s input, then manipulate, analyze, and modify it. The string entered will go through several functions and print out statements according to the input entered. • Ask the user to input string or paragraph, then enter a character either a-z or A-Z later on
in the program.
  - Print an error message if the user enters anything invalid (non-character value) then prompt them to enter another value.

## Four Functions in The Program 
At the beginning of the program, the user will be given to choose any of the functions below. After they've chosen a function, they will be prompted to enter a string or paragraph to perform the operations on.

**1. Check if the number of vowels equals the number of consonants**
- If user enters `banana` , program will print `# vowels = # consonants.`
- If user enters `zip` , program will print  `# vowels != # consonants.`

**2. Letter Swap**

The user will be prompted to enter two letters, the C-style string that was received before will be modified to replace the first letter with the second letter.

- If user's string is: `Let's eat potatoes` , and the first character chosen is `o` and second character chosen is `i`, the user will receive :
      
       The modified string is: 
       Let's eat pitaties 

**3. Temporarily flip the C-style string**

The program will create a new C-style string from the heap where the C-style string given by the user will be reversed. 

- If the user's string is `night` , the user will receive `thgin` as an output.

**4. Swap lower case with upper case letters**

- If the user's string is `unItEd` , the user will receive `UNiTeD` as an output.

## Command
To run the program, run: 

      g++ assignment4.cpp
      
Then, run:
  
      ./a.out

## Requirements

- Use loops to avoid code duplication
- Use functions to define re-usable modules of code. Must have at least 3 functions to calculate flight duration, calculate flight cost per passenger, and output flight animation.
- At least 1 function should specify a default value for at least 1 parameter.
- Check all user inputs and handle invalid inputs gracefully
- No use of global variables




