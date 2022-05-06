# Client-Server Chat
###### CS 372 Portfolio Assignment - Winter 2022 at Oregon State University

## Description

This is a Client/Server chat program where the server does not handle multiple clients 
and only one socket connection is made. This socket will be reused for the life of the
program. 

## Commands 

To run the program, do the following:

1. Run the server.py with `python3 server.py`
2. Then, run the client program with `python3 client.py`


## Specification for The Assignment

Server: 
1. The server creates a socket and binds to 'localhost' and port xxxx
2. The server then listens for a connection
3. When connected, the server calls recv to receive data
4. The server prints data, then prompts for a reply
5. If the reply is /q, the server quits
6. Otherwise, the server sends reply
7. Back to step 3
8. Sockets are closed

Client: 
1. The client creates a socket and connects to ‘localhost’ and port xxxx
2. When connected, the client prompts for a message to send
3. If the message is /q, the client quits
4. Otherwise, the client sends the message
5. The client calls recv to receive data
6. The client prints the data
7. Back to step 2
8. Sockets are closed
