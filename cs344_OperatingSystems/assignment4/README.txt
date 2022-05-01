Name: Kathleen Ashley
ONID: 934239494
CS 344 - Winter 2022
Assignment 4(Line_processor) - Due on 02/21/2022
============================================================================================

Instructions: 

1) Compile the program with Makefile:
    
     make

    Compiling the program without Makefile: 

    gcc --std=gnu99  line_processor.c -o line_processor -lm -pthread

2) Run the program with: 

    [with input/output redirection]:

    ./line_processor < [input_file_name.txt] > [output_file_name.txt]

    [without input/output redirection]:

    ./line_processor

================
    CITATION: 
================
    1. The code that was provided in the exploration (Unbounded Producer-Consumer)
        was used to create some functions in this code.
        URL : https://replit.com/@cs344/64prodconsunboundc#main.c

    2. The code that was provided in the exploration/assignment 4 page (6.5 prod_cons_pipeline.c)
        was used to implement this project, and most of the put/get buffer functions were based on 
        the functions that were provided in that file.
        URL : https://replit.com/@cs344/65prodconspipelinec
    
    3. The functions that modified the input sentences (changing '\n' to ' ' or '++' to '^')
        utilized some of the functions I coded previously for assignment 3 - smallsh. 

