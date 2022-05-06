import socket 
import sys

#------------------------------------------------------------------------------------------
#	CODE CITATION
#------------------------------------------------------------------------------------------
# 1. Used this URL : https://realpython.com/python-sockets/#application-client-and-server
#    to understand better the concept behind client-server connection (also with statements)
#    and also used the logic behind it to create this code.
# 2. The first project of our class also helped the structure of this assignment. 
# 3. URL: https://www.geeksforgeeks.org/with-statement-in-python/
# 	 Helped understanding the 'with' statements in python3
#------------------------------------------------------------------------------------------


# Variables
loopAgain = 0
hostName = "localhost"
data = ""
userInput = ""
counter = 0

# Ask the user for the port number
portString = input("Enter the port number: ")
clientPort = int(portString)

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)


with clientSocket as clientConn:
	# Setting up a connection between the server and the client before 
	# we could receive data from the server.
	clientConn.connect((hostName, clientPort))

	# While loop again is true (depending on whether the input is valid,
	# then keep on looping.
	while (loopAgain == 0):
		# if user input is not /q, then keep on receiving data from server
		# and alsoo prompts client for input.
		if userInput != "/q":
			del userInput
			data = clientConn.recv(1024)
			decodedData = data.decode()
			print(decodedData)

			# if this is the first iteration, the server is sending two messages
			# that must be received, that's why the counter is here.
			if counter == 0:
				del data
				data = clientConn.recv(1024)
				decodedData = data.decode()
				print(decodedData)
				counter+= 1

			# After receiving data from the server, prompt the user to enter input.
			userInput = input("> ")
			encodedInput = userInput.encode()

			# sending message to server.
			clientConn.sendall(encodedInput)
		# If the input is /q, then quit.
		elif userInput == "/q":
			loopAgain = 1