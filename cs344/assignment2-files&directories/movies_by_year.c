/* 
    Name: Kathleen Ashley
    OSU ID: 934239494
    Operating Systems, Winter 2022
    Project 2 - movies by year
*/

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

#define prefix "movies_"
#define dirSize 21


struct movie
{
    char *title;
    char *year;
    char *languages[5];
    char *rating;
    int languageC;
    struct movie *next;
};

// Citation: 
// This function was taken from the students.c material that was given
// to help with this assignment.
struct movie *createMovie(char *currLine)
{
    struct movie *mov = malloc(sizeof(struct movie));

    // used for strtok_r
    char *save;
    char *save2;
    char comma[] = ",";
    int holder;
    int counter = 0;

    // 1. Moving the title data to struct
    char *token = strtok_r(currLine, comma, &save);
    mov->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->title, token);

    // 2. Moving the year data to struct
    token = strtok_r(NULL, comma, &save);
    mov->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->year, token);

    save2 = save;

    // 3. Moving the languages data and rating data to struct
    while((token = strtok_r(NULL, "[];,", &save2)))
    {
        // convert the token to int. 
        holder = atoi(token);

        // if holder is 0, it means that the string contains
        // alphanumeric characters.
        if(holder == 0)
        {
            mov->languages[counter] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(mov->languages[counter], token);
            counter++;
        }
        // if it falls under this case, it means that holder holds the value of ratings.
        else
        {
            mov->languageC = counter;
            mov->rating = calloc(strlen(token) + 1, sizeof(char));
            strcpy(mov->rating, token);
        }
    }

    mov->next = NULL;

    return mov;
}

// Citation: 
// This function was taken from the students.c material that was given
// to help with this assignment.
struct movie *processFile(char *filepath)
{
    FILE *mov = fopen(filepath, "r");

    if(mov == NULL)
    {
        printf("Error %d \n", errno);
        exit(1);
    }

    char *curr = NULL;
    size_t len = 0;
    size_t nread;
    int counter = 0;

    struct movie *head = NULL;
    struct movie *tail = NULL;

    // get the getline to move past the first line in the file.
    size_t firstLine = (getline(&curr, &len, mov) != '\n');
    // need to use this if function to get rid of unused variable warning.
    if(firstLine != 0)
    {
        // creating a linked list line by line.
        while((nread = getline(&curr, &len, mov)) != -1)
        {
            counter++;
            struct movie *newNode = createMovie(curr);
            if(head == NULL)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    //printf("\nProcessed file %s and parsed data for %d movies.\n\n", filepath, counter);

    free(curr);
    fclose(mov);
    return head;
}

// ==================================== DESCRIPTION ===================================
// CheckInput function: 
// Checks the input and make sure that it is within reasonable range that is between 1-4.
// Citation: 
// This checking function was inspired (not copied verbatim) from assignment5 in CS161 
// that I did back in winter 2020 in C++.
//======================================================================================
void checkInput(int *value, int low, int high)
{
    int copy = *value;
    int stillFalse = 0;

    // As long as the input is still not valid, keep on repeating the while loop.
    while(stillFalse == 0)
    {
        if(copy >= low && copy <= high)
        {
            // if input is finally within range, change value to the value that copy holds.
            stillFalse = 1;
            *value = copy;
        }
        else
        {
            printf("ERROR: Option is not within range. Please enter a number between %d and %d: ", low, high);
            scanf("%d", &copy);
        }
    }
}

// ==================================== DESCRIPTION ===================================
// CheckInput function: 
// Checks the year of the input entered by user, and ensures that it is within range. 
// In this case, the input should be between 1900 and 2021.
// Citation: 
// This checking function was inspired (not copied verbatim) from assignment5 in CS161 
// that I did back in winter 2020 in C++.
//======================================================================================
void checkYear(int *value)
{
    int copy = *value;
    int stillFalse = 0;

    while(stillFalse == 0)
    {
        // checks whether the year is within the inclusive range of 
        // year 1900 and 2021.
        if(copy >= 1900 && copy <= 2021)
        {
            stillFalse = 1;
            *value = copy;
        }
        else
        {
            printf("ERROR: Option is not within range. Please enter a number between 1900-2021: ");
            scanf("%d", &copy);
        }
    }
}

// ========================== DESCRIPTION =============================
// yearExists():
// this function returns 1 if the year that was given by the program 
// does not exist inside the file. Otherwise, return 0.
//=====================================================================
int yearExists(struct movie *data, int year)
{
        struct movie *tmp = data;
        int yearHolder = 0;
        int noData = 0;

        while(tmp != NULL)
        {
            // converts the string tmp->year into int.
            yearHolder = atoi(tmp->year);
            // checks and see if any of the year in the struct matches the one
            // asked by the program.
            if(yearHolder == year)
            {
                noData = 1;
            }
            tmp = tmp->next;
        }

        // if there is no data found within that year, return 1.
        if(noData == 0)
        {
            return 1;
        }

        return 0;
}

// ========================== DESCRIPTION =============================
// printFirstOption: 
// print the movies released within a specific year into the output.
//=====================================================================
void printFirstOption(struct movie *data, int year, char *fileData)
{
    struct movie *tmp = data;
    int yearHolder = 0;
    char movieData[1024] = "";

    while(tmp != NULL)
    {
        // converts the string tmp->year into int.
        yearHolder = atoi(tmp->year);
        // checks and see if any of the year in the struct matches the one
        // asked by user.
        if(yearHolder == year)
        {
            strcat(movieData, tmp->title);
            strcat(movieData, "\n");
        }
        tmp = tmp->next;
    }
    strcpy(fileData, movieData);
    strcpy(movieData, "");
}

// ========================== DESCRIPTION =====================================
// printSecondOption: 
// print the highest rated movie per year, along with its year, rating and title.
//==============================================================================
void printSecondOption(struct movie *data)
{
    struct movie *highestRM;
    struct movie *tmp = data;

    // used as a flag to see if the year's been found in the data
    // before or not.
    int yearFound = 1;

    // holders for the rating data.
    double tmpRating = 0;
    double highestRating = 0;
    int currYear;
    int year;
    int counter = 0;
    char *holder1;
    char *holder2;


    for(year = 1900; year <= 2021; year++)
    {
        counter++;
        // goes through the linked list one by one and compare the rating
        while (tmp != NULL)
        {
            currYear = atoi(tmp->year);
            if(year == currYear)
            {
                // if this is the first time year is found in the data,
                // set highestRM to the data tmp holds.
                if(yearFound == 1)
                {
                    yearFound = 0;
                    highestRM = tmp;
                }
                // if it falls underneath this condition, compare
                // the ratings of the movie with the highest one known so far.
                else if(yearFound == 0)
                {
                    tmpRating = strtod(tmp->rating, &holder1);
                    highestRating = strtod(highestRM->rating, &holder2);
                    if(tmpRating > highestRating)
                    {
                        highestRM = tmp;
                    }
                }
            }
            tmp = tmp->next;
        }

        // if a movie exists within that year, then there must be a highest rated movie.
        // print the information.
        if(yearFound == 0)
        {
            highestRating = strtod(highestRM->rating, &holder2);
            printf("%s %.1f %s\n", highestRM->year, highestRating, highestRM->title);
        }

        // make sure tmp points to the first item in the list.
        tmp = data;
        // reset yearFound to 1.
        yearFound = 1;
    }
}

// ========================== DESCRIPTION =============================
// printThirdOption:
// Print all the movies that have the language given by the user.
//=====================================================================
void printThirdOption(struct movie *data, char *lang)
{
    struct movie *tmp = data;
    int noData = 0;

    // Goes through the linked list
    while(tmp != NULL)
    {  
        // find a substring within that string. In this case,
        // see if the language entered by user exists in the 
        // file by going through the languages array in each movie.
        for(int i = 0; i < tmp->languageC; i++)
        {
            if(strstr(tmp->languages[i], lang) != NULL)
            {
                noData = 1;
                printf("%s %s\n", tmp->year, tmp->title);
            }
        }
        tmp = tmp->next;
    }

    // if there is no data, which is caught by the flag noData, 
    // then print the statement below.
    if(noData == 0)
    {
        printf("There is no movie in the list released in %s\n", lang);
    }

    printf("\n");
}

// ========================== DESCRIPTION ======================================
// randomizeNum:
// This function randomizes numbers and puts the value inside the variable *num
// that was passed by reference.
//===============================================================================
void randomizeNum(int *num)
{
    srand(time(NULL));
    *num = rand() % (99999 + 1 - 0);
}

// ========================== DESCRIPTION =============================
// freeLinkedList: 
// This function frees the memory that was used to make the linked list!
//======================================================================
void freeLinkedList(struct movie *data)
{
    struct movie *holder;

    while(data != NULL)
    {
        holder = data;
        data = data->next;

        free(holder->title);
        free(holder->year);

        for(int i = 0; i < holder->languageC; i++)
        {
            free(holder->languages[i]);
        }

        free(holder->rating);
        free(holder);
        holder = NULL;
    }
}

// ========================== DESCRIPTION =============================================
// writeToFile() :
// This function takes the data from the file that was given, 
// and separates them into a few files based on the year a movie was created.
// It then compiles all movies that were produced in the same year and put it into 
// a file named after that year.
//======================================================================================
void writeToFile(struct movie *tmp, char *dirName)
{
    struct movie *list = tmp;
    char fileName[10];
    char fileData[1024];

     // check between the year 1900 and 2021, see if any of the movies 
     // in the list were between those years, if so return 0.
    for(int year = 1900; year <= 2021; year++)
    {
        
        strcpy(fileName, "");
        if(yearExists(list, year) == 0)
        {
            sprintf(fileName, "%d", year);
            strcat(fileName, ".txt");

            // making the filePath for fopen()
            char filePath[32] = "./";
            strcat(filePath, dirName);
            strcat(filePath, "/");
            strcat(filePath, fileName);

            // Code citation: 
            // This code was adapted from class exploration.
            // This was taken from: 3_4_read.c 
            int fd;
            fd = open(filePath, O_RDWR | O_CREAT | O_TRUNC, 0640);

            if(fd == -1)
            {
                printf("open() failed");
                exit(1);
            }

            printFirstOption(list, year, fileData);
            write(fd, fileData, strlen(fileData));
            close(fd);
        }
    }
}

// ========================== DESCRIPTION =============================
// checkIfFileExists()
// This function checks whether a fileName that was given by the user
// actually exists in that current directory.
//=====================================================================
int checkIfFileExists(char *fileN)
{
    // Code citation: 
    // This code was inspired by a class material that was given 
    // as a resource. 
    // Name of file: 3_4_directory.c
    DIR *currDir = opendir(".");
    struct dirent *aDir;

    while((aDir = readdir(currDir)) != NULL)
    {
        // check whether the file name matches with one of the files
        // in the directory
        if(strcmp(aDir->d_name, fileN) == 0)
        {
            return 0;
        }
    }
    closedir(currDir);
    return 1; 
}

int main(int argc, char *argv[])
{   
    // Variables
    int keepOnLooping = 1;
    char *extension = ".csv";
    char *nameOfSmallestF = NULL;
    char *nameOfBiggestF = NULL;
    int sizeHolder = 0;
    int counter = 0;
    int firstInput = 0;
    int secondInput = 0;
    struct stat dirStat;
    char pathway[32] = "ashleyk.movies.";
    int randomNum = 0;
    char randomChar[6];
    int check;
    char fileN[30];
    int innerLoop = 1;
    int err = 0;

    while(keepOnLooping == 1)
    {
        if(err == 0)
        {
           printf("\n1. Select file to process\n");
           printf("2. Exit the program\n\n");
           printf("Enter a choice 1 or 2: ");
           scanf("%d", &firstInput);
           checkInput(&firstInput, 1,2);
        }

        innerLoop = 1;

        while(innerLoop == 1)
        {
            err = 0;

            if(firstInput == 1)
            {
                printf("\nWhich file do you want to process?\n");
                printf("Enter 1 to pick the largest file\n");
                printf("Enter 2 to pick the smallest file\n");
                printf("Enter 3 to specify the name of a file\n\n");
                printf("Enter a choice from 1 to 3: ");
                scanf("%d", &secondInput);

                checkInput(&secondInput, 1,3);

                // Code citation: 
                // This code was adapted from class exploration material,
                // Name of the code on Replit: 3_t_stat_example.c
                // opens current directory
                DIR *currDir = opendir(".");
                struct dirent *aDir;

                // 1. If the user chooses option 3, ask for a filename and check whether or not 
                //    that file exists in the current directory.

                if(secondInput == 3)
                {
                    printf("Enter the complete file name: ");
                    scanf("%s", fileN);

                    int result = checkIfFileExists(fileN);
                    innerLoop = result;
                    if(result == 1)
                    {
                        printf("The file %s was not found. Try again\n", fileN);
                        err = 1;
                        break;
                    }
                    printf("Now processing the chosen file named: %s\n", fileN);
                }

                // 2. Compare and see which is the smallest and biggest files in the current directory.

                if(secondInput == 1 || secondInput == 2)
                {
                    while((aDir = readdir(currDir)) != NULL)
                    {
                        // checking the prefix of the file which should be movies_
                        if(strncmp(prefix, aDir->d_name, strlen(prefix)) == 0)
                        {
                            stat(aDir->d_name, &dirStat);

                            // check whether the file ends with .csv
                            if(strstr(aDir->d_name, extension) != NULL)
                            {
                                // if it is the first time this loop goes through the directory,
                                // set the first file as the biggest/smallest file.
                                if(counter == 0)
                                {
                                    if(secondInput == 1)
                                    {
                                        nameOfBiggestF = aDir->d_name;
                                        sizeHolder = dirStat.st_size;
                                    }
                                    if(secondInput == 2)
                                    {
                                        nameOfSmallestF = aDir->d_name;
                                        sizeHolder = dirStat.st_size;
                                    }
                                }
                                else
                                {
                                    if(secondInput == 1)
                                    {
                                            if(dirStat.st_size > sizeHolder)
                                            {
                                                nameOfBiggestF = aDir->d_name;
                                                sizeHolder = dirStat.st_size;
                                            }
                                    }
                                    if(secondInput == 2)
                                    {
                                        if(dirStat.st_size < sizeHolder)
                                        {
                                            nameOfSmallestF = aDir->d_name;
                                            sizeHolder = dirStat.st_size;
                                        }
                                     }
                                }
                            }
                            counter++;
                        }
                    }
                    if(secondInput == 1)
                    {
                        printf("Now processing the chosen file named: %s\n", nameOfBiggestF);
                    }
                    if(secondInput == 2)
                    {
                        printf("Now processing the chosen file named: %s\n", nameOfSmallestF);
                    }
                }
                             
                // 3. Making the directory for the files to be put in.

                    // randomize the number to put at the end of the directory pathway
                    randomizeNum(&randomNum);
                    sprintf(randomChar, "%d", randomNum);
                    // concatenate the string of random number to the dir prefix.
                    strncat(pathway, randomChar, 5);
                    printf("Created directory with name: %s\n", pathway);

                    // allocate memory for the directory name
                    char dirName[1024]; 
                    strcpy(dirName, pathway);

                    // Make the directory, giving the owner read, write and execution permission
                    // While only giving group read and execute permission to the directory.
                    check = mkdir(dirName, 0750);

                    if(check == -1)
                    {
                        printf("Directory couldn't be made\n");
                    }
                
                // 4. Parsing data from the file.

                    struct movie *list;

                    if(secondInput == 1)
                    {
                        list = processFile(nameOfBiggestF);
                    }
                    if(secondInput == 2)
                    {
                        list = processFile(nameOfSmallestF);
                    }
                    if(secondInput == 3)
                    {
                        list = processFile(fileN);
                    }

                // 5. Write the movies found within certain years, and put them
                //  in a file in the directory that was made.
                    
                writeToFile(list, dirName);

                // once it is finished, restore pathway to ".ashleyk.movies."
                strcpy(pathway, "ashleyk.movies.");
                freeLinkedList(list);
                closedir(currDir);
                innerLoop = 0;
            }
            else if(firstInput == 2)
            {
                keepOnLooping = 0;
                innerLoop = 0;
            }
        }
    }

    return 0;
}