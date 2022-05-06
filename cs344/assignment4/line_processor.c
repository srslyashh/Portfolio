#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h> 
#include <string.h>
#include <ctype.h>

// GLOBALS 
#define NUM_LINES 50
#define NUM_INPUT 1000

// set to 0 to print all the debug within this code.
int debug = 1;

/*
    Down below are the attributes of buffer 1-3 that were modified and taken from 
    6_5 pipeline-prod-cons.c that were given as a class material to be used in helping
    to make this assignment.
*/
// Buffer 1, shared resource between input thread and line separator thread
    char buffer_1 [50][1000];
    int count_1 = 0;
    int prod_idx_1 = 0;
    int con_idx_1 = 0;
    pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;


// Buffer 2, shared resource between line separator thread and plus sign thread
    char buffer_2 [50][1000];
    int count_2 = 0;
    int prod_idx_2 = 0;
    int con_idx_2 = 0;
    pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;

// Buffer 3, shared resource between plus sign thread and output thread
    char buffer_3 [50][1000];
    int count_3 = 0;
    int prod_idx_3 = 0;
    int con_idx_3 = 0;
    pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;


  /*
      CODE!
  */

  /*
    put_buff_1: 
      Put the modified sentence/input into buffer1.
    
    Citation: 
      This function was modified and inspired from 6-5 pipeline producer and consumer
      from exploration.
  */
  void put_buff_1(char *input)
  {
    pthread_mutex_lock(&mutex_1);

    if(debug == 0)
    {
      printf("input: %s\n", input);
    }

    strcpy(buffer_1[prod_idx_1], input);

    prod_idx_1++;
    count_1++;

    pthread_cond_signal(&full_1);
    pthread_mutex_unlock(&mutex_1);
  }

  /*
    getInput: 
      Gets the input from user/file.

    Citation: 
      This function was modified and inspired from 6-5 pipeline producer and consumer
      from exploration.
  */
  void *getInput(void *args)
  {
    int loopAgain = 0;
    char input[NUM_INPUT];
    char comparison[6] = "STOP\n";

    // since we do not accept more than 50 lines of input.
    for(int i = 0; i < 50; i++)
    {
      fgets(input, 1000, stdin);

      // if fgets encounters "STOP\n", then stop 
      // getting input from user. Mark the end of the file with -1 (END_MARKER)
      if(strcmp(input, comparison) == 0)
      {
        // changing i to 49 so it'll stop the for loop.
        i = 49;
        put_buff_1("-1");
      }
      // if strcmp is not 0, then the token that was encountered
      // is not "STOP\n". Put the string in buffer.
      else
      {
        put_buff_1(input);
      }
    }
    return NULL;
  }

/*
  get_buff_1: 
    Gets the input from buffer 1. 
  
  Citation: 
    This function was modified and taken from 6-5 pipeline producer and consumer
    from exploration.
*/
char *get_buff_1()
{
  char *input;

  pthread_mutex_lock(&mutex_1);

  while (count_1 == 0)
  {
    pthread_cond_wait(&full_1, &mutex_1);
  }

  if(debug == 0)
  {
    printf("File: %s\n", buffer_1[con_idx_1]);
  }
  
  // Allocating memory for input with the size of the string to be copied.
  strcpy(input=(char*)malloc(sizeof(buffer_1[con_idx_1])), buffer_1[con_idx_1]);

  if(debug == 0)
  {
    printf("input1: %s\n", input);
  }

  con_idx_1++;
  count_1--;

  pthread_mutex_unlock(&mutex_1);

  return input;
}

/*
  get_buff_2: 
    Gets the input from buffer 2. 
  
  Citation: 
    This function was modified and taken from 6-5 pipeline producer and consumer
    from exploration.
*/
char *get_buff_2()
{
  char *input;

  pthread_mutex_lock(&mutex_2);

  while (count_2 == 0)
  {
    pthread_cond_wait(&full_2, &mutex_2);
  }

  if(debug == 0)
  {
    printf("File: %s\n", buffer_2[con_idx_2]);
  }
  
  // Allocating memory for input with the size of the string to be copied.
  strcpy(input=(char*)malloc(sizeof(buffer_2[con_idx_2])), buffer_2[con_idx_2]);

  if(debug == 0)
  {
    //printf("input1: %s\n", input);
  }

  con_idx_2++;
  count_2--;

  pthread_mutex_unlock(&mutex_2);

  return input;
}

/*
  get_buff_3: 
    Gets the input from buffer 3. 

  Citation: 
    This function was modified and taken from 6-5 pipeline producer and consumer
    from exploration.
*/
char *get_buff_3()
{
  char *input;

  pthread_mutex_lock(&mutex_3);
  while (count_3 == 0)
  {
    pthread_cond_wait(&full_3, &mutex_3);
  }

  if(debug == 0)
  {
    printf("File: %s\n", buffer_3[con_idx_3]);
  }
  
  // Allocating memory for input with the size of the string to be copied.
  strcpy(input=(char*)malloc(sizeof(buffer_3[con_idx_3])), buffer_3[con_idx_3]);

  if(debug == 0)
  {
    //printf("input1: %s\n", input);
  }

  con_idx_3++;
  count_3--;

  pthread_mutex_unlock(&mutex_3);

  return input;
}

/*
  put_buff_2: 
  Put the modified input (after replacing '\n' with ' ') to buffer 2. 
  
  Citation: 
    This function was modified and taken from 6-5 pipeline producer and consumer
    from exploration.
*/
void put_buff_2(char *input)
{
  // Lock the mutex before putting the item in the buffer
  pthread_mutex_lock(&mutex_2);

  // copy the input to buffer 2!
  strcpy(buffer_2[prod_idx_2], input);

  prod_idx_2++;
  count_2++;

  pthread_cond_signal(&full_2);

  pthread_mutex_unlock(&mutex_2);
}

/*
  changeList; goes through the array and adds ' ' if there's a '\n'.
  checks if the last element before '\n' is a space, if so, skips 
  so there'll only be one space.

  Citation: 
    This function was coded by me for assignment 3 - smallsh. This function was 
    modified and used approriately to fit this assignment.
*/
void changeList(char *args, int stop)
{
    char holder[NUM_INPUT] = "";
    int length = strlen(args);
    int lastElement = stop - 1;
    int spaceFlag;

    // copy the first few characters before '\n'
    for(int i = 0; i < stop; i++)
    {
      if(i == lastElement)
      {
        spaceFlag = isspace(args[i]);

        // if the end is not a space, then copy it to the new char array.
        // if it is a space, skip!
        if(spaceFlag == 0)
        {
          holder[i] = args[i];
        }
      }
      else
      {
        holder[i] = args[i];
      }
    }
    
    // concatenate space to the end of the string.
    strcat(holder, " ");

    // set lenStart to where stop was + 1.
    int lenStart = 1 + stop;

    // start where args[i] was left off and keep on 
    // copying to the holder array.
    for(int i = stop; i < length - 1; i++)
    {   
      holder[lenStart] = args[i];
      lenStart++;
    }
    
    // copy holder to args!
    strcpy(args, holder);
}

/*
  compareChar: 
   checks if char a and b are equal, if so, return 0. otherwise 
   return 1.

  Citation: 
    This function was coded by me for assignment 3 - smallsh. This function was 
    modified and used approriately to fit this assignment.
*/
int compareChar(char a, char b)
{
  if(a == b)
  {
    return 0;
  }
  return 1;
}


/*
  goThroughList: 
  goes through the list and check if there's '\n', and call changeList
  to replace '\n' with a space.

  Citation: 
    This function was coded by me for assignment 3 - smallsh. This function was 
    modified and used approriately to fit this assignment.
*/
void goThroughList(char *args)
{
  int lenOfArg = strlen(args);

  for(int i = 0; i < lenOfArg; i++)
  {
    if(compareChar(args[i], '\n') == 0)
    {
      changeList(args, i);
      
      if(debug == 0)
      {
        printf("String: %s", args);
      }
    }
  }
}

/*
  replaceWithSpace:
    go through the input, and find '\n'. Modify that to ' '. 
  
  Citation: 
    This function was inspired from 6.4 Unbounded producer and consumer
    file that was provided in the exploration.
*/
void *replaceWithSpace(void *args)
{
  int loopAgain = 0;
  char *input;
  int counter = count_1;
  int holder = NUM_LINES;

  while(loopAgain == 0)
  {
    input = get_buff_1();

    // the use of -1 to mark the end of the input.
    if(strcmp(input, "-1") == 0)
    {
      loopAgain = 1;
    }

    // goes through the list and replace '\n' with ' '.
    goThroughList(input);

    // put the modified input into buffer 2.
    put_buff_2(input);
  }

  return NULL;
}

/*
  replace: 
    search ++ signs and replace them with '^'. 
  
  Citation: 
    This function was modified from the one that I coded 
    for Assignment 3 - smallsh.
*/
void replace(char *args, int stop)
{
    char holder[NUM_INPUT] = "";
    int length = strlen(args);
    //printf("length: %d\n", length);

    // copy the first few characters before '++'
    for(int i = 0; i < stop; i++)
    {
        holder[i] = args[i];
    }
    
    // concatenate '^' to the string where ++ was found.
    strcat(holder, "^");

    // set lenStart to where stop was + 1.
    int lenStart = 1 + stop;

    // start where args[i] was left off and keep on 
    // copying to the holder array.
    for(int i = stop + 2; i < length; i++)
    {   
      //printf("args: %c, i: %d \n", args[i], i);
      holder[lenStart] = args[i];
      lenStart++;
    }
    
    // copy holder to args!
    strcpy(args, holder);
}

/*
  searchAndReplace: 
    search ++ signs and replace them with '^'. 
  
  Citation: 
    This function was modified from the one that I coded 
    for Assignment 3 - smallsh.
*/
void searchAndReplace(char *args)
{
  int lenOfArg = strlen(args);

  for(int i = 0; i < lenOfArg; i++)
  {
    if(compareChar(args[i], '+') == 0)
    {
        if(compareChar(args[i+1], '+') == 0)
        {
            replace(args, i);
        }
    }
  }
}

/*
  put the modified input (after having ++ replaced by ^)to buffer 3. 

  Citation:   
    This function was modified and taken from 6-5 pipeline producer and consumer
    from exploration.
*/
void put_buff_3(char *args)
{
  pthread_mutex_lock(&mutex_3);

  // copies the modified argument into buffer 3.
  strcpy(buffer_3[prod_idx_3], args);

  prod_idx_3++;
  count_3++;

  pthread_cond_signal(&full_3);
  pthread_mutex_unlock(&mutex_3);
}

/*
  replacePlusSigns:
    In this function, we replace the ++ sign with ^.
    This function is gonna call searchAndReplace where the index where ++ was found is 
    going to be noted and replaced by ^.
*/
void *replacePlusSigns(void *args)
{
  int loopAgain = 0;
  char *input;

  while(loopAgain == 0)
  {
    input = get_buff_2();

    if(strcmp(input, "-1") == 0)
    {
      loopAgain = 1;
    }

    //printf("String: %s\n", input);
    searchAndReplace(input);

    // after the string is modified, put it into buffer3.
    put_buff_3(input);
  }

  return NULL;
}

/*
    copyChar: copy the char string to be printed to screen/file.
    make sure that each sentence only contains 80 characters without
    newline character.
*/
void copyChar(char *destination, char *copy, int *counterChar)
{
  int counter = 0;
  char holder[NUM_INPUT] = "";
  int holdCC = *counterChar;

  // while counter is less than 80, keep on copying the character
  // to holder.
  while(counter < 80)
  {
    holder[counter] = copy[holdCC];
    counter++;
    holdCC++;
  }

  // append a newline character at the end of the string.
  strcat(holder, "\n");

  //printf("strlen: %d", strlen(holder));
  *counterChar = counter + *counterChar;
  
  strcpy(destination, holder);
}

/*
  write_output: 
    In this function, we write the output whether to screen/ to a file that has been 
    indicated by the user.
*/
void *write_output(void *args)
{
  int loopAgain = 0;
  char *input;

  // 80 character line + '\n'.
  char output[82];
  char fileHolder[50000];
  int tempLength = 0;
  int counterChar = 0;
  int diff = 0;
  int noMorePrint = 0;
  int numLines = 0;
  int linesPrinted = 0;

  while(loopAgain == 0)
  {
    input = get_buff_3();
    strcat(fileHolder, input);
    //printf("file holder: %s\n", fileHolder);

    // make sure we don't print out "-1" to the screen/file.
    if(strcmp(input, "-1") == 0)
    {
      loopAgain = 1;
    }
    else
    {
      tempLength = strlen(fileHolder);
      diff = tempLength - counterChar;

      // We compute the number of lines that can be printed by 
      // counting the length of fileHolder and dividing it by 80.
      numLines = tempLength / 80;

      // As long as the number of lines to be printed is less than the lines 
      // that have been printed, keep on looping.
      while(numLines > linesPrinted)
      {
        //printf("diff: %d, counterchar : %d, strlen: %d\n", diff, counterChar, tempLength);

        if(diff >= 80)
        {
          copyChar(output, fileHolder, &counterChar);
          //printf("%d\n", counterChar);

          printf("%s", output);
          linesPrinted++;

          // cleaning out output by copying an empty string to it before use.
          strcpy(output, "");
        }
      }
    }
  }
  return NULL;
}

int main()
{
    // initializing the threads
    pthread_t inputT, lineSepT, plusSignT, outputT;

    // Create the threads
    pthread_create(&inputT, NULL, getInput, NULL);
    pthread_create(&lineSepT, NULL, replaceWithSpace, NULL);
    pthread_create(&plusSignT, NULL, replacePlusSigns, NULL);
    pthread_create(&outputT, NULL, write_output, NULL);

    // Wait for the threads to terminate
    pthread_join(inputT, NULL);
    pthread_join(lineSepT, NULL);
    pthread_join(plusSignT, NULL);
    pthread_join(outputT, NULL);

    return EXIT_SUCCESS;
}