import socket 

# Variables
request = '/wireshark-labs/HTTP-wireshark-file3.html';
hostName = 'gaia.cs.umass.edu';
reqHost = 'GET /wireshark-labs/HTTP-wireshark-file3.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n'
serverPort = 80;
message = ''
endM = ''
lenM = 0
lenEnd = 0


# Printing the Header
print('Request: ' + request)
print('Host: ' + hostName)
print('\n')

# Code
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Setting up a connection between the server and the client before 
# we could receive data from the server.
s.connect((hostName, serverPort))

# Sending the GET request 
s.sendall(reqHost)

# Citation for the loop below
# Date: 01/22/2022
# Adapted some ideas from Baris Usakli's post on Stack Overflow that 
# touched on the subject of looping until recv receives 0 bytes of message
# URL : https://stackoverflow.com/questions/16745409/what-does-pythons-socket-recv-return-for-non-blocking-sockets-if-no-data-is-r

# Explanation: Looping until recv() returns 0 bytes in the loop
# or in this case, until message contains nothing
# but an empty string.
while True: 
	message = s.recv(1024)

	# Keep track of the length of the message
	lenM = len(message)

	# if message was 0 (did not contain anything)
	# then break from loop.
	if message == '':
		break

	# append the current message to the end message to be printed
	endM += message
	# accumulate the length of the message
	lenEnd += lenM

print('[RECV] - length: ' + str(lenEnd))
print(endM)
s.close()