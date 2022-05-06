#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netdb.h>      
#include <ctype.h>

/*
    Citation: 

      Used the skeleton code provided by the instructor for 
      client.c to make this assignment, so some codes and functions 
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
  exit(0); 
} 

/*
  receiveData() function: 
    receiveData from the client side.

    CITATION: 
      modified the code that was provided by the instructor (Ryan Gambord) in 
      ed discussion for the recv() and send() functions. 

      URL: https://edstem.org/us/courses/16718/discussion/1241674
*/
void receiveData(int dataLength, char* destination, int socketC)
{
  int totalData = 0;
  int currData = 0;
  char accData[100000];
  char holder[100000];
  
  memset(accData, '\0', sizeof(accData));
  memset(destination, '\0', sizeof(destination));
  while(totalData < dataLength)
  {
    currData = recv(socketC, holder, sizeof(holder) -1, 0); 
    if(currData < 0)
    {
      fprintf(stderr, "ERROR: reading from socket\n");
      exit(1);
    }
    else
    {
      strcat(accData, holder);
      totalData = totalData + currData;
      memset(holder, '\0', sizeof(holder));
    }
  }

  strcpy(destination, accData);
}

/*
  checkBadInput():
    Check if the textfile/keyfile has bad inputs. 
*/
void checkBadInput(const char* file, int *size, char *destination)
{
  int dataSize = 0;
  char checkIn;
  int loopAgain = 0;
  FILE *input = fopen(file, "r");

  // Try to open the file and if the client cannot open the file,
  //give an error.
  if(file = NULL)
  {
    fprintf(stderr, "ERROR: Could not open file for input\n");
    exit(1);
  }

  // Otherwise, count the amount of characters in the data while also 
  // checking if the file contains any bad input.
  while(loopAgain == 0)
  {
    checkIn = fgetc(input);

    // if the character that fgetc returns is EOF or \n, 
    // then break out of the loop.
    if(checkIn == EOF || checkIn == '\n')
    {
      loopAgain = 1;
    }
    // if the character is not a capital letter, not a ' ' or '\0',
    // it must be a bad character. 
    else if(isupper(checkIn) == 0 && checkIn != ' ' && checkIn != '\0')
    {
      fprintf(stderr, "ERROR: File contains bad characters.\n");
      exit(1);
    }
    // if loopAgain is still true, put in the character that was validated
    // in the destination char holder.
    if(loopAgain == 0)
    {
      destination[dataSize] = checkIn;
      dataSize++;
    }
  }
  // change the sizeholder to dataSize (to keep track of the length of the file)
  *size = dataSize;
  fclose(input);
}

// Set up the address struct
/*
  Citation: 
    Used the skeleton code provided by the instructor for 
    client.c to make this assignment, so some codes and functions 
    were used from the skeleton code.
*/
void setupAddressStruct(struct sockaddr_in* address, int portNumber, char* hostname)
{
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);

  // Get the DNS entry for this host name
  struct hostent* hostInfo = gethostbyname(hostname); 
  if (hostInfo == NULL) 
  { 
    fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
    exit(0); 
  }
  // Copy the first IP address from the DNS entry to sin_addr.s_addr
  memcpy((char*) &address->sin_addr.s_addr, 
        hostInfo->h_addr_list[0],
        hostInfo->h_length);
}

/*
  sendData():
    send the encrypted message to the client.

    CITATION: 
      modified the code that was provided by the instructor (Ryan Gambord) in 
      ed discussion for the recv() and send() functions. 

      URL: https://edstem.org/us/courses/16718/discussion/1241674
*/
void sendData(int dataLength, char *source, int socketC)
{
  int totalSent = 0;
  int currSent = 0;
  int lenHolder = dataLength;

  // keep on looping while total data sent to the client is less than the 
  // dataLength.
  while(totalSent < dataLength)
  {
    currSent = send(socketC, ((char *) source) + totalSent, lenHolder - totalSent , 0);
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
  int socketFD, portNumber, charsWritten, charsRead;
  struct sockaddr_in serverAddress;
  char buffer[256];
  char key[100000];
  char data[100000];
  char autKey[30];
  char authenticate[25];
  char encrypted[100000];
  int dataSize = 0;
  int keySize = 0;
  int loopAgain = 0;
  int dataSent = 0;
  int totalData = 0;
  int charsReceived = 0;
  int charsSent = 0;

  // Check usage & args
    if (argc < 3) 
    { 
      fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); 
      exit(0); 
    } 
  
  // Create a socket
    socketFD = socket(AF_INET, SOCK_STREAM, 0); 
    if (socketFD < 0)
    {
      fprintf(stderr, "CLIENT: ERROR opening socket\n");
      exit(1);
    }

   // Set up the server address struct
    setupAddressStruct(&serverAddress, atoi(argv[3]), "localhost");

    // Connect to server
    if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
      fprintf(stderr, "CLIENT: ERROR connecting\n");
      exit(1);
    }
  
    // Checking to see if the plaintext file has any bad characters
    dataSize = 0;
    keySize = 0;

    //printf("Checking data\n");
    checkBadInput(argv[1], &dataSize, data);
    //printf("Checking key\n");
    checkBadInput(argv[2], &keySize, key);

    if(keySize < dataSize)
    {
      fprintf(stderr,"ERROR: key file is smaller than the plaintext file.\n");
      exit(1);
    }

    // Here, we are gonna send an acknowledgement to let the server know
    // who they are communicating with. 
    // We're gonna send "enc_client/dataSize" so that the server would know how much data
    // they are expecting to receive
    char dsize[25];
    memset(authenticate, '\0', sizeof(authenticate));
    strcat(authenticate, "dec_client/");

    // As the size of data and key would be the same, we only need to 
    // send the length of the data to the server. 
    sprintf(dsize, "%d", dataSize);
    strcat(authenticate, dsize);
    strcat(authenticate, "\n");

    //printf("authenticate: %s\n", authenticate);

    // sending the authentication.
    charsSent = send(socketFD, authenticate, strlen(authenticate), 0);
    if(charsSent < 0)
    {
      fprintf(stderr, "ERROR: Could not send data to server\n");
      exit(1);
    }
    
    memset(autKey, '\0', strlen(autKey));

    while(loopAgain == 0)
    {
      charsReceived = recv(socketFD, autKey, sizeof(autKey) - 1, 0);
      //printf("key recv: %s\n", autKey);
      if(charsReceived < 0)
      {
        fprintf(stderr, "ERROR: Receiving data from server failed\n");
        exit(1);
      }
      else
      {
        loopAgain = 1;
        int innerLoop = 0;

        // If the server validates our connection, then proceed with sending the data.
        if(strcmp(autKey, "Valid") == 0)
        {
          // printing test cases
          //printf("Here\n");
          //printf("data: %s\n", data);
          //printf("key: %s\n", key);
          
          // sending the data from file.
          sendData(dataSize, data, socketFD);
          // sending data from key
          sendData(dataSize, key, socketFD);
        }
        else if(strcmp(autKey, "Invalid") == 0)
        {
          // if it's not dec_server, it's gonna run to this print statement.
          fprintf(stderr, "ERROR: Client-server connection was invalid.\n");
          exit(2);
        }
      }
    }
    
  // add one to dataSize as we are also accepting the data + newline character.
  receiveData(dataSize, encrypted, socketFD);
  strcat(encrypted, "\n");
  printf("%s", encrypted);

  // Close the socket
  close(socketFD); 
  return 0;
}