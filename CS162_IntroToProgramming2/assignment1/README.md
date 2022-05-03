# The Wizard Spellbook Catalog
###### CS 162 - Fall 2020

## Description
A C++ program that asks user to input 2 existing files, then based on those two files, create a spell book catalog where accessing restrictions and searching for spell books could be done. The program needs to ensure that these two files exist, before continuing. The first existing file will contain spell book information and spell book that the program will display. The second existing file will contain the list of wizards that can have access. After confirming that these two files exist, the program will continue to wizard login where the user is prompted to enter an ID and password. The ID must be all integer, and both the ID and password have to match with the information given in one of the files.

## Requirements

**1. Requirements Command Line Arguments**

When starting the program, the user will provide two command line arguments. The first command line argument will be the name of the file that holds the information about the wizards. The second command line argument will be the name of the file that contains the information about spellbooks and included spells. If the user does not provide two names of existing files the program should print out an error message and quit. You can assume that the user always provides these two command line arguments in the correct order.

**2. Wizard Login**

Before the user can get information from the program they must login. You must prompt the user for an ID and password. The ID of the must be all integers. If it isn’t, you must re-prompt the user for an ID that is only ints. You will then prompt the user for the password. The password will be a string that could contain any number of characters and numbers. You do not need to do any error handling on the password. You will then need to check this information against the wizard_info.txt file contents to determine which wizard is logging in. If there is no match, you must reprompt for both username and password again. If the user fails to login a$er three a%empts, you must provide an error message and quit out of the program. (Note: If the user provides an ID that is not all integers that should not count as an error towards the three a%empts that they have to login). A$er a user logs in, you must display the corresponding name, ID, school position, and beard length

**3. Sorting and Printing**

Once the user has logged in they should be prompted with a list of different ways to display the sorted spellbook and spell information. 
- Wizards with student status cannot view any spell that has an effect of death or poison and cannot view any spellbook with a spell that has an effect of death or poison. 
- After the user has chosen an option, they should be asked if they want the information printed to the screen or wri%en to a file. If they choose to write to a file, they should be prompted for a file name. 
  - If the file name already exists, the information should be appended to the file. 
  - If the file name does not exist, a file should be created and the information should be written to the file. For your sorting, you cannot use the built-in sort function.
 
## Available Options (after successful login)

**1. Sort spellbooks by number of pages**
   
  If the user picks this option the books must be sorted in ascending order by number of pages. 
   - Books with a spell that have an effect of death or poison should not be displayed when a student is logged in (i.e. hide those books from the results when a student is logged in). Once they are sorted, you should print/write to file the title of the book and the number of pages it has.
 
**2. Sort spells by effect**

There are five types of spells: fire, bubble, memory_loss, death, poison. 
- Remember that students cannot see spells that have the type death or poison. 
- The spells with bubbles as the effect should be listed first, followed by memory_loss, fire, poison, and death. Once they are sorted, you should print/write to file the spell name and its effect.

**3. Sort by average success rate of spells**

You must create a list of books sorted by the average success rate of all the spells contained within the book. Once calculated, you should print/write to file the title of each applicable book and the corresponding average success rate. Books with a spell that have an effect of death or poison should not be displayed when a student is logged in (i.e. hide those books from the results when a student is logged in).

**4. Quit: The program will exit.**

Your program should continue sorting and printing/writing until the user chooses to quit.
