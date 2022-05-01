Name: Kathleen Ashley
ONID: 934239494
CS 344 - Winter 2022
Assignment 1 (Movies) - due on 01/17/2022
============================================================================================

Description: 

In this program, you'll be able to get some information based on the data that you provide
and the options you choose (there are three options). In the first option, the program
will show you the movies within that specified year. In ths second option, the program will
show you the highest rated movie each year, and in the third option, the program will 
show you the title and year of all movies in a specific language.

Instructions: 

1) Compile the program with: 
    
     make

2) Run the program with: 

    ./movies [the name of the file from which the data will be taken]

    ex: 
        ./movies movies_sample_1.csv

3) You will be told how many movies were parsed and where the data was taken from by the program.

4) You will be given this menu: 

    1. Show movies released in the specified year
    2. Show highest rated movie for each year
    3. Show the title and year of release of all movies in a specific language
    4. Exit from the program

    The program expects the input to be an integer and will check if it is within range (1-4).

    If the input was not valid, the program will give you an error and reprompt you for another input.

    Depending on the option you choose, you will get different responses.

    ==================
    (1) First option: 
    ==================

    The program will then prompt you to enter the year in which you want to see the movies. 

        If there exists a movie within the year that you specified, the program will print out 
        a list of all the movie titles. 

        Ex: 
             Enter the year for which you want to see the movies: 2012
             The Avengers
             Rise of the Guardians
             Anna Karenina

        If there are no movies in the year that you specified, the program will output this: 

            Enter the year for which you want to see the movies: 1999
            There is no movie in the list released in the year 1999
    
    ==================
    (2) Second option: 
    ==================

    The program will print out the highest rated movie for each year! The list will also
    be printed with the year in an ascending order.

        Ex: 
            The highest rated movie for each year: 
            2003 6.6 Right on Track
            2008 7.9 Iron Man
            2009 7.6 Sherlock Holmes
            2010 7.0 Iron Man 2
            2011 7.0 Thor
            2012 8.1 The Avengers
            2013 7.2 Iron Man 3
            2014 7.8 Captain America: The Winter Soldier
            2015 7.4 Avengers: Age of Ultron
            2016 7.8 Captain America: Civil War
            2017 7.9 Thor: Ragnarok
            2018 8.5 Avengers: Infinity War

    ==================
    (3) Third option: 
    ==================

    The program will print out the movies in the language that you specified. 

        If there exists a movie with the language that was specified, 
        the program will print out a list. 

        Ex: 
            Enter the language for which you want to see the movies: Swedish
            2016 Revolting Rhymes Part One

        However, if there is no movie in the language that was specified, the 
        program will print out: 

            Enter the language for which you want to see the movies: swedish
            There is no movie in the list released in swedish

    *note: 
        The program is case-sensitive, therefore the result for swedish and Swedish
        are not the same. 


    ==================
    (4) Fourth option: 
    ==================

    The program will stop prompting you with the options and quit. Thank you for playing! 


=========================================================================================

    [LIMITATIONS]

    1. This program expects the input from the user to be of type integer at the beginning
        and will only check to see if the integer is within range. 

=========================================================================================

    [CITATIONS]

    1. The document students.c that was given as a resource to help with this program was
        used to help with parsing the data. 
    2. The function checkYear() and checkInput() were inspired from error-checking functions
        back in CS 161 from assignment 5 that I coded in Winter 2020. These codes were not
        copied verbatim and were just used as an inspiration for the error-checking functions
        in this assignment.
