#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void randomizeKey(int keyLength)
{
    srand(time(NULL));
    char key[keyLength + 1];
    char keyArr[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int randomNum = 0;

    // Generate a key array that is as long as the keyLength requested
    // by user.
    for(int i = 0; i < keyLength; i++)
    {
        randomNum = rand() % 26;
        key[i] = keyArr[randomNum];

        if(i == keyLength - 1)
        {
            key[keyLength] = '\0';
        }
    }

    // Print the key.
    printf("%s\n", key);
}

int main(int argc, char *argv[])
{
    int keyLength = 0;
    
    if(argc < 2)
    {
        printf("ERROR: Length of arguments is less than 2.");
        exit(0);
    }

    // make keyLength equal to the length entered by the user.
    keyLength = atoi(argv[1]);
    randomizeKey(keyLength);

    return 0;
}