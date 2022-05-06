import socket 

# Variables
reqHost = '127.0.0.1'
serverPort = 52730;
message = ''
data  = "HTTP/1.1 200 OK\r\n"\
"Content-Type: text/html; charset=UTF-8\r\n\r\n"\
"<html>Congratulations! You've downloaded the first Wireshark lab file!</html>\r\n"


# Code
print('Connected by: (' + reqHost + ', ' + str(serverPort) + ')')
print('\n')

# Citation for the following code: 
# Date: 01/23/2022
# Adapted from course material: Kurose & Ross, Computer Networking
# Page: 196
serverS = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Associating the serverPort with 127.0.0.1
serverS.bind((reqHost, serverPort))

# Make sure that the program listens to any client 
serverS.listen(1)

# This line below listens to any connection requests 
# made to the server
connectionS, addr = serverS.accept()

message = connectionS.recv(1024)

print('Received: ' + str(message))

# Sending the data to the client
connectionS.send(data.encode())

print('\n')
print('Sending >>>>>>>>>>')
print(str(data))
print('<<<<<<<<<<<<<<<<<<')

connectionS.close()