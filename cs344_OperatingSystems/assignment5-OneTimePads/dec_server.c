#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
    Citation: 

      Used the skeleton code provided by the instructor for 
      server.c to make this assignment, so some codes and functions 
      were used from the skeleton code.
*/

// Error function used for reporting issues
/*
  Citation: 
    A function provided from the skeleton code.
*/
void error(const char *msg) 
{
  perror(msg);
  exit(1);
} 

// Set up the address struct for the server socket
/*
  Citation: 
    A function provided from the skeleton code.
*/
void setupAddressStruct(struct sockaddr_in* address, int portNumber)
{
  memset((char*) address, '\0', sizeof(*address)); 
  address->sin_family = AF_INET;
  address->sin_port = htons(portNumber);
  address->sin_addr.s_addr = INADDR_ANY;
}

/*
  receiveData() function: 
    receiveData from the client side.

    CITATION: 
      modified the code that was provided by the instructor (Ryan Gambord) in 
      ed discussion for the recv() and send() functions. 

      URL: https://edstem.org/us/courses/16718/discussion/1241674
*/
void receiveData(int dataLength, char* destination, int connectionS)
{
  int totalData = 0;
  int currData = 0;
  char accData[100000];
  char holder[100000];
  
  // clear out the accData and destination
  memset(accData, '\0', sizeof(accData));
  memset(destination, '\0', sizeof(destination));

  // while totalData is less than the datalength intended, 
  // keep on looping. 
  while(totalData < dataLength)
  {
    currData = recv(connectionS, holder, sizeof(holder) -1, 0); 
    if(currData < 0)
    {
      fprintf(stderr, "ERROR: reading from socket\n");
      exit(1);
    }
    else
    {
      // concatenate the result to accData
      strcat(accData, holder);
      totalData = totalData + currData;
      memset(holder, '\0', sizeof(holder));
    }
  }
  // copy the string that was received to the destination.
  strcpy(destination, accData);
}

/*
  getIndex():
    returns the index of the character.
*/
int getIndex(char alp)
{
  char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  int index = 0;

  for(int i = 0; i < 27; i++)
  {
    if(alphabet[i] == alp)
    {
      index = i;
    }
  }
   // because A is at index 0, we are gonna shift the character
  // arrays by 1 so A will start at 1. This is done so the 
  // encryption and decryption can work.
  return index + 1;
}

/*
  getAlpha():
    get the character of the index that is requested.
*/
char getAlpha(int index)
{
  char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
  // minus it by 1, because we shifted the character array by 1.
  index -= 1;
  return alphabet[index];
}

/*
  decryptData:
    decrypt data that is received by client.
*/
void decryptData(char *message, char *key, char *dest, int dataLength)
{
  int messageArr[100000];
  int keyArr[100000];
  char decrypt[100000];
  int messageIndex = 0;
  int keyIndex = 0;
  int holder = 0;
  
  for(int i = 0; i < dataLength; i++)
  {
    // Get the size of the messageIndex and keyIndex.
    messageIndex = getIndex(message[i]);
    keyIndex = getIndex(key[i]);

    // subtract the messag index by the key index.
    holder = getIndex(message[i]) - getIndex(key[i]);

    // If holder is equal or less than 0 (negative number),
    // then we add 27 to it.
    if(holder <= 0)
    {
      holder = holder + 27;
    }

    // Send it to the decryption function.
    decrypt[i] = getAlpha(holder);
    //printf("%d: %c\n", i, decrypt[i]);
  }

  decrypt[dataLength] = '\n';
  strcpy(dest, decrypt);
}

/*
  sendData():
    send the encrypted message to the client.

    CITATION: 
      modified the code that was provided by the instructor (Ryan Gambord) in 
      ed discussion for the recv() and send() functions. 

      URL: https://edstem.org/us/courses/16718/discussion/1241674
*/
void sendData(int dataLength, char *source, int connectionS)
{
  int totalSent = 0;
  int currSent = 0;
  int lenHolder = dataLength;

   // keep on looping while total data sent to the client is less than the 
  // dataLength.
  while(totalSent < dataLength)
  {
    currSent = send(connectionS, ((char *) source) + totalSent, lenHolder - totalSent , 0);
    if(currSent < 0)
    {
      fprintf(stderr, "ERROR: Could not send data to server\n");
      exit(1);
    }
    // if currSent is bigger than 0, make sure that gets added to totalSent.
    else
    {
      totalSent = totalSent + currSent;
    }
  }
}

int main(int argc, char *argv[])
{
  int connectionSocket, charsRead;
  int charsSent = 0;
  int dataLength = 0;
  char buffer[256];
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);

  //printf("Hello\n");
  // Check usage & args
    if (argc < 2) 
    { 
      fprintf(stderr,"USAGE: %s port\n", argv[0]); 
      exit(1);
    } 
  
  // Create the socket that will listen for connections
    int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0) 
    {
      fprintf(stderr,"ERROR opening socket");
      exit(1);
    }

  // Set up the address struct for the server socket
    setupAddressStruct(&serverAddress, atoi(argv[1]));

    if (bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
      fprintf(stderr, "ERROR on binding.\n");
      exit(1);
    }

  listen(listenSocket, 5); 

  // Accept a connection, blocking if one is not available until one connects
    while(1)
    {
      // wait for request from client
      connectionSocket = accept(listenSocket, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); 
      if(connectionSocket < 0)
      {
        error("ERROR on accept");
      }

      // if connection is accepted, then fork. 
      pid_t pidHolder = fork();

      switch(pidHolder)
      {
          case -1:
            fprintf(stderr, "ERROR: fork() has failed.\n");
            exit(1);
            break;
          
          // if it falls underneath this case, then the request will be processed and 
          // message will be sent to the connection.
          case 0:
          {
            char dataInChar[26];
            char message[1001];
            char data[100000];
            char *save;
            char *autKey;
            char authenticate[25];
            char decrypted[100000];
            char key[100000];
            int dataReceived = 0;

            // responses
            char val[6] = "Valid";
            char inv[8] = "Invalid";

            // first receive the handshake (make sure it's from enc_client!)
            memset(authenticate, '\0', 25);
            charsRead = recv(connectionSocket, authenticate, 24, 0);
            if(charsRead < 0)
            {
              fprintf(stderr, "ERROR: reading from socket\n");
              exit(1);
            }
            else
            {
              /*
                The authentication key sent by the client should be in this format: 
                  filname/dataLength\n

                  so for dec_client, the authentication key would be:
                  dec_client/dataLength\n.
              */
              autKey = strtok_r(authenticate, "/", &save);

               // if it is dec_client, then proceed to tokenize the rest of the message 
              // that was received. 
              if(strcmp(autKey, "dec_client") == 0)
              {
                //printf("here. checking if enc_client\n");
                // now, we split the message again to get the size of the message to be sent.
                autKey = strtok_r(NULL, "\n", &save);
                strcpy(dataInChar, autKey);

                // turn the string of dataSize to int.
                dataLength = atoi(dataInChar); 

                //printf("datalength; %d\n", dataLength);

                // send authentication to client. 
                charsSent = send(connectionSocket, val, strlen(val), 0); 
                if(charsSent < 0)
                {
                  fprintf(stderr, "ERROR: Failed to send authentication from server\n");
                  exit(1);
                }

                // Receive data from textfile
                receiveData(dataLength, data, connectionSocket);
                // Receive data from key
                receiveData(dataLength, key, connectionSocket);

                // encrypting the message!
                decryptData(data, key, decrypted, dataLength);
                //printf("Decrypt: %s", decrypted);

                // sending encrypted data to client. 
                sendData(dataLength, decrypted, connectionSocket);
              }
              // if it is not enc_client, don't connect
              else if(strcmp(autKey, "enc_client") != 0)
              {
                //printf("Hm\n");
                charsSent = send(connectionSocket, inv, strlen(inv), 0); 
                if(charsSent < 0)
                {
                  fprintf(stderr, "ERROR: Failed to send authentication from server\n");
                  exit(1);
                }
                fprintf(stderr, "ERROR: Connection was invalid.\n");
                exit(1);
              }
            }
            exit(0);
          }
          default:
            close(connectionSocket);
      }
    }
  
  // Close the listening socket
  close(listenSocket); 
  return 0;
}
