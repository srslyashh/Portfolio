import socket 
import sys

#------------------------------------------------------------------------------------------
#	CODE CITATION
#------------------------------------------------------------------------------------------
# 1. Used this URL : https://realpython.com/python-sockets/#application-client-and-server
#    to understand better the concept behind client-server connection (also with statements)
#    and also used the logic behind it to create this code. 
# 2. Used this URL : https://stackoverflow.com/questions/55032621/oserror-errno-57-socket-is-not-connected
# 	 to help fix some errors that were caused by .setsockopt(), problem was solved
#	 by adding socket. in front of SQL_SOCKET and SO_REUSEADDR.
# 3. The first project of our class also helped the structure of this assignment.
# 4. URL: https://www.geeksforgeeks.org/with-statement-in-python/
# 	 Helped understanding the 'with' statements in python3
#------------------------------------------------------------------------------------------


# Variables
hostName = "localhost"
data = ""
serverMsg = ""
loopAgain = 0

# Ask the user for the port number
portString = input("Enter the port number: ")
serverPort = int(portString)

serverS = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverS.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)


with serverS as conn:
	conn.bind((hostName, serverPort))

	# Make sure that the program listens to any client 
	conn.listen(1)

	print("Server listening on: " + hostName + " on port: " + portString)

	# This line below listens to any connection requests made to the server
	connectionS, addr = serverS.accept()

	with connectionS: 
		strAdd = str(addr)

		# printing these messages on the server side.
		print("Connected by ('" + strAdd + "', port: " + portString + ")")
		print("Waiting for message from client..")

		# sending these messages to client as instructions
		typeM = "Type /q to quit"
		enterM = "Enter message to send.."
		connectionS.sendall(typeM.encode())
		connectionS.sendall(enterM.encode())

		while(loopAgain == 0):
			# here we clean out the data and serverMsg strings
			# so it'll be empty strings at every iteration.
			del data
			del serverMsg

			# receiving data and decoding them
			data = connectionS.recv(1024)
			decodedData = data.decode()

			# compare and see if the decoded data is '/q', if it is,then quit. 
			if decodedData == "/q" or not data:
				loopAgain = 1
			# Else, print the message and ask the server for input.
			elif decodedData != "/q":
				print(decodedData)
				serverMsg = input("> ")
				connectionS.sendall(serverMsg.encode())


