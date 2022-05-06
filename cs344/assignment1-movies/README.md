# Movies
#### CS 344 - Winter 2022 at Oregon State University

## Command 

1) Compile the program with: 
    
        make

2) Run the program with: 

        ./movies [the name of the file from which the data will be taken]

    ex: 
    
        ./movies movies_sample_1.csv

## Expectations 

Write a program that: 
- Reads a CSV file with movie data that is provided to the program as an argument
- Processes the data in the file to create structs to hold data for each movie
- Creates a linked list of all these structs
- Gives user choices to ask questions about the movies in the data
- Prints out the data about the movies per user choice

## Functionalities of the Program

### Process the input file

The program must read all data from the file given and process it. After processing the file, the program must print the message below to stdout: 

    "Processed the file XYZ and parsed data for M movies" 

where XYZ is the name of the file that has been processed and M is the number of movies whose data has been processed.

### Interactive functionality

The program should show a menu of interactive options to the user and process the selected option as described below. 

#### 1. Show movies released in the specified year

The program will then prompt you to enter the year in which you want to see the movies. 

- If there exists a movie within the year that you specified, the program will print out a list of all the movie titles. 

    Ex: 
    
           Enter the year for which you want to see the movies: 2012
           
           The Avengers
           Rise of the Guardians
           Anna Karenina

- If there are no movies in the year that you specified, the program will output this: 

            Enter the year for which you want to see the movies: 1999
            
            There is no movie in the list released in the year 1999
            
#### 2. Show highest rated movie for each year  

If the user chooses this option, then for each year for which at least one movie was released, display a movie that had the highest rating along with the year and the rating with one line per year. The list will also
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
            
#### 3. Show movies and their year of release for a specific language 

The program will print out the movies in the language that you specified. 

- If there exists a movie with the language that was specified, the program will print out a list. For instance: 
    
            Enter the language for which you want to see the movies: Swedish
            2016 Revolting Rhymes Part One

- However, if there is no movie in the language that was specified, the program will print out: 

            Enter the language for which you want to see the movies: swedish
            There is no movie in the list released in swedish
            
***NOTE:*** 
  *The program is case-sensitive, therefore the result for swedish and Swedish are not the same.* 
            
#### 4. Exit 

The program will stop prompting you with the options and quit. 

#### NOTES on the functionalities
- If the user enters an incorrect integer, the program will print out an errorr message and again present the 4 options to the user.
- The program assumes that when it asks the user to enter an integer, the user will indeed enter an integer.
- The program won't assume the languages in the test file will be the same as the ones that appear in the sample file.

## Technical Requirements

Program is required to: 
1. Read data from the file line by line
2. Break-up the line into tokens
3. Create a struct called movie with the data for that line
4. Create a linked list containing all the movie structures

## Sample Program Execution 
```
$ ./movies movies_sample_1.csv 
Processed file movies_sample_1.csv and parsed data for 24 movies

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 1
Enter the year for which you want to see movies: 1999
No data about movies released in the year 1999

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 1
Enter the year for which you want to see movies: 2012
The Avengers
Rise of the Guardians
Anna Karenina

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 2
2008 7.9 Iron Man
2009 7.6 Sherlock Holmes
2010 7.0 Iron Man 2
2013 7.2 Iron Man 3
2017 7.9 Thor: Ragnarok
2012 8.1 The Avengers
2016 7.8 Captain America: Civil War
2018 8.5 Avengers: Infinity War
2015 7.4 Avengers: Age of Ultron
2011 7.0 Thor
2014 7.8 Captain America: The Winter Soldier
2003 6.6 Right on Track

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 3
Enter the language for which you want to see movies: English
2008 The Incredible Hulk
2009 Sherlock Holmes
2008 Iron Man
2010 Iron Man 2
2013 Iron Man 3
2017 Thor: Ragnarok
2012 The Avengers
2016 Doctor Strange
2018 Avengers: Infinity War
2015 Avengers: Age of Ultron
2011 Thor
2013 Thor: The Dark World
2017 Spider-Man: Homecoming
2011 Captain America: The First Avenger
2016 Captain America: Civil War
2015 Ant-Man
2014 Captain America: The Winter Soldier
2018 Mary Queen of Scots
2016 Revolting Rhymes Part One
2017 The Glass Castle
2016 Free Fire
2003 Right on Track
2012 Rise of the Guardians
2012 Anna Karenina

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 3
Enter the language for which you want to see movies: Punjabi
No data about movies released in Punjabi

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 5
You entered an incorrect choice. Try again.

1. Show movies released in the specified year
2. Show highest rated movie for each year
3. Show the title and year of release of all movies in a specific language
4. Exit from the program

Enter a choice from 1 to 4: 4
$
```
