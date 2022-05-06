Name: Kathleen Ashley
ONID: 934239494
CS 344 - Winter 2022
Assignment 5: One Time Pads - Due on 03/07/2022
============================================================================================

Instructions: 

1) Compile the program with Makefile first:
    
    make

2) After compiling the program with the makefile, Run the program with: 

    enc_server [listening_port] &

    enc_client [filename] [filename for key] [port number]

    keygen [size] > [filename]

    dec_server [listening_port] &

    dec_client [filetobedecrypted] [filename for key] [port number]

================
    CITATION: 
================
    1. The code that was provided in the exploration (server.c and client.c)
        were used as skeleton code to both dec_server.c and dec_client.c
    2. Modified the code that was provided by the instructor (Ryan Gambord) in 
        ed discussion for the recv() and send() functions. 
        URL: https://edstem.org/us/courses/16718/discussion/1241674
