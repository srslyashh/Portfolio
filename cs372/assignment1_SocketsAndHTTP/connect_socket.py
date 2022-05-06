import socket 
import sys

# Variables
request = 'GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1';
hostName = 'gaia.cs.umass.edu';
reqHost = 'GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n'
serverPort = 80;
message = ''
endM = ''
sizeM = 0
sizeEnd = 0

# Printing the Header
print('Request: ' + request)
print('Host: ' + hostName)
print('\n')

# Code

# Citation for the following code: 
# Date: 01/23/2022
# Adapted from course material: Kurose & Ross, Computer Networking
# Page: 194

#This line creates the client's socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Setting up a connection between the server and the client before 
# we could receive data from the server.
s.connect((hostName, serverPort))

# Citation for s.sendall() and understanding GET
# Date: 01/22/2022
# Understanding get() and sendall() from stack overflow from a post made  by Mhawke.
# URL : https://stackoverflow.com/questions/34192093/python-socket-get
# Sending the GET request
s.sendall(reqHost)

# Citation for s.recv()
# Date: 01/22/2022
# Received understanding on recv() function from Tdelaney's post.
# URL : https://stackoverflow.com/questions/41382127/how-does-the-python-socket-recv-method-know-that-the-end-of-the-message-has-be

# Taking data in from the server, accumulating all the characters
# in the variable message, then end it once it reaches the end of 
# the line.

message = s.recv(1024)

print('[RECV] - length: ' + str(len(message)))
print(message)
s.close()