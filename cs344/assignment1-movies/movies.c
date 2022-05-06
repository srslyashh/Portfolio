/* 
    Name: Kathleen Ashley
    OSU ID: 934239494
    Operating Systems, Winter 2022
    Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct movie
{
    char *title;
    char *year;
    char *languages;
    char *rating;
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
    char comma[] = ",";

    // 1. Moving the title data to struct
    char *token = strtok_r(currLine, comma, &save);
    mov->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->title, token);

    // 2. Moving the year data to struct
    token = strtok_r(NULL, comma, &save);
    mov->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->year, token);

    // 3. Moving the languages data to struct
    token = strtok_r(NULL, comma, &save);
    mov->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->languages, token);
    
    // 4. Moving the rating data to struct
    token = strtok_r(NULL, "\n", &save);
    mov->rating = calloc(strlen(token) + 1, sizeof(char));
    strcpy(mov->rating, token);

    mov->next = NULL;

    return mov;
}

// Citation: 
// This function was taken from the students.c material that was given
// to help with this assignment.
struct movie *processFile(char *filepath)
{
    FILE *mov = fopen(filepath, "r");

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

    printf("\nProcessed file %s and parsed data for %d movies.\n\n", filepath, counter);

    free(curr);
    fclose(mov);
    return head;
}

// CheckInput function: 
// Checks the input and make sure that it is within reasonable range that is between 1-4.
// Citation: 
// This checking function was inspired (not copied verbatim) from assignment5 in CS161 
// that I did back in winter 2020 in C++.
void checkInput(int *value)
{
    int copy = *value;
    int stillFalse = 0;

    // As long as the input is still not valid, keep on repeating the while loop.
    while(stillFalse == 0)
    {
        if(copy >= 1 && copy <= 4)
        {
            // if input is finally within range, change value to the value that copy holds.
            stillFalse = 1;
            *value = copy;
        }
        else
        {
            printf("ERROR: Option is not within range. Please enter a number between 1-4: ");
            scanf("%d", &copy);
        }
    }
}

// CheckInput function: 
// Checks the year of the input entered by user, and ensures that it is within range. 
// In this case, the input should be between 1900 and 2021.
// Citation: 
// This checking function was inspired (not copied verbatim) from assignment5 in CS161 
// that I did back in winter 2020 in C++.
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

// printFirstOption: 
// print the movies released within a specific year into the output.
void printFirstOption(struct movie *data, int year)
{
    struct movie *tmp = data;
    int yearHolder = 0;
    int noData = 0;

    while(tmp != NULL)
    {
        // converts the string tmp->year into int.
        yearHolder = atoi(tmp->year);
        // checks and see if any of the year in the struct matches the one
        // asked by user.
        if(yearHolder == year)
        {
            printf("%s\n", tmp->title);
            noData = 1;
        }
        tmp = tmp->next;
    }

    // if there is no data found, this will print.
    if(noData == 0)
    {
        printf("There is no movie in the list released in the year %d\n", year);
    }

    printf("\n");
}

// printSecondOption: 
// print the highest rated movie per year, along with its year, rating and title.
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

// printThirdOption:
// Print all the movies that have the language given by the user.
void printThirdOption(struct movie *data, char *lang)
{
    struct movie *tmp = data;
    int noData = 0;

    // Goes through the linked list
    while(tmp != NULL)
    {  
        // find a substring within that string. In this case,
        // see if the language entered by user exists in the 
        // file.
        if(strstr(tmp->languages, lang) != NULL)
        {
            noData = 1;
            printf("%s %s\n", tmp->year, tmp->title);
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

int main(int argc, char *argv[])
{
    // checking to see if the argument entered is less than 2 (no filename), 
    // if so, exit program.

    if(argc < 2)
    {
        printf("ERROR: You need to enter a filename!\n");
        return 1;
    }

    struct movie *list = processFile(argv[1]);
    
    // 1. process the file
    int keepOnLooping = 1;
    int input = 0;
    int year = 0;
    char lang[20];

    while(keepOnLooping == 1)
    {
        printf("1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Quit the program\n");
        printf("Enter a choice from 1 to 4: ");
        scanf(" %d", &input);
        printf("\n");

        checkInput(&input);

        if(input == 1)
        {
            printf("Enter the movies for which you want to see the movies: ");
            scanf("%d" , &year);

            checkYear(&year);
            printFirstOption(list, year);
        }
        if(input == 2)
        {
            printf("The highest rated movie for each year: \n");
            printSecondOption(list);
            printf("\n");
        }
        if(input == 3)
        {
            printf("Enter the language for which you want to see the movies: ");
            scanf("%s", lang);

            printThirdOption(list, lang);
        }
        if(input == 4)
        {
            keepOnLooping = 0;
        }
    }

    return 0;
}