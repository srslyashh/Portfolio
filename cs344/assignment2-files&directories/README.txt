Name: Kathleen Ashley
ONID: 934239494
CS 344 - Winter 2022
Assignment 2 (Movies by Year) - due on 01/17/2022
============================================================================================

Description: 

In this program, the user will be able to get some information based on the data that they provide
and the options you choose. They'll be first given 2 options (whether to process a file or quit),
then they'll be given three options which is for the program to pick the largest file, smallest file,
or a file that has been requested specifically by the user. 

Instructions: 

1) Compile the program with Makefile:
    
     make

    Compiling the program without Makefile: 

    gcc --std=gnu99 -o movies_by_year movies_by_year.c

2) Run the program with: 

    ./movies_by_year
    
3) You will be given this menu: 

    1. Select file to process
    2. Exit the program

    The program expects the input to be an integer and will check if it is within range (1-2).

    If the input was not valid, the program will give you an error and reprompt you for another input.

    Depending on the option you choose, you will get different responses.

    ==================
    (1) First option: 
    ==================

    The program will then give you another menu: 

        Which file do you want to process?
        Enter 1 to pick the largest file
        Enter 2 to pick the smallest file
        Enter 3 to specify the name of a file
    
        The program will go through all the files with the prefix movies_ in the current directory
        with the file extension .csv for option 1 and 2.

        For option 3, the program will prompt the user to enter a filename (including the extension)

        ex: 
            Enter the complete file name: hello.csv


    The program will then let the user know which file is being processed:

        ex:
            Now processing the chosen file named: hello.csv


    For all three options, the program will parse the data within the file chosen. The program 
    will create files with 4 digit integer value (representing the year the movies in that file
    were made). The permission on these files will be set to rw-r-----.

        The file 2012.txt will contain the following movie titles:
        Ex: 
             The Avengers
             Rise of the Guardians
             Anna Karenina

    These files then will be put in a new directory that the program has made under 
    ashleyk.movies.randomNum . This directory's permission will be set to rwxr-x---.
        - randomNum is going to be a random number between 0 and 99999.

    ==================
    (2) Second option: 
    ==================

    The program will stop prompting you with the options and quit. Thank you for playing! 


=========================================================================================

    [LIMITATIONS]

    1. This program expects the input from the user to be of type integer at the beginning
        and will only check to see if the integer is within range. 
    2. This program is not going to check whether there is no file in the directory when 
        the user chooses option 1 and 2 (look for the biggest and smallest files in the 
        current directory).

=========================================================================================

    [CITATIONS]

    1. Some of the codes that were used as a resource to help with this program was taken 
        from the class exploration. They were: 
            - 3_5_open_close.c
            - 3_4_directory.c
            - 3_4_read.c
    2. The function checkYear() and checkInput() were inspired from error-checking functions
        back in CS 161 from assignment 5 that I coded in Winter 2020. These codes were not
        copied verbatim and were just used as an inspiration for the error-checking functions
        in this assignment.


