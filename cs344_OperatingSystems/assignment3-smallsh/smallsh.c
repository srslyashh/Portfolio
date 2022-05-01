#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

/* 
    VARIABLES AND FUNCTIONS USED FOR THE PROGRAM.
*/ 

// CONSTANTS
#define maxArguments 512
#define maxCommandLength 2048

// global variable
pid_t backgroundPid[maxArguments];
int countBackPid = 0;
char *startDir;
char *newDir;
int isBackground = 1;
int isForeground = 0;
int onlyForeground = 1;
int childStatus;
char *backRedirection = "/dev/null";

struct input
{
    char *list[maxArguments];
    int commandCounter;
    int noInput;
    char *inputF;
    char *outputF;
    int isInputF;
    int isOutputF;
    int isAmpersand;
};

// function declarations
void goThroughList(char *);
int searchForSign(char *);
void printProcessStat(pid_t, int*);
void statusFunc();
void handle_SIGCHLD(int);

// Initialize sigint_action & sigstp_action
struct sigaction SIGINT_action = {{0}}, SIGTSTP_action = {{0}}; 



/* 
    CODE
*/ 

struct input *getInput(char *inp)
{
    struct input *holder =  malloc(sizeof(struct input));

    char input[maxArguments];
    char *token;
    char *save;
    int lenOfArgument;
    int commandC = 0;
    int emptyFlag = 0;
    int inputFlag = 0;
    int outputFlag = 0;
    int counter = 0;

    printf(": ");
    fflush(stdout);
    fgets(input, maxArguments, stdin);

    // substituting instances of '$$' into the pid number.
    goThroughList(input);
    strcpy(inp, input);

    // removing the newline character from input
    input[strcspn(input,"\n")] = 0;
    lenOfArgument = strlen(input);

    if(lenOfArgument == 0)
    {
        holder->noInput = 0;
        emptyFlag = 1;
    }
    else if(lenOfArgument == 1)
    {
        if(strcmp(input, " ") == 0)
        {
            holder->noInput = 0;
            emptyFlag = 1;
        }
    }

    // break the input into tokens and put them in char *command[maxArgs]
    if(emptyFlag != 1)
    {
        token = strtok_r(input, " ", &save);
        counter += strlen(token) + 1;
        
        if(strcmp(token, "") == 0 ||  strcmp(token, "#") == 0 || searchForSign(input) == 0)
        {
            holder->noInput = 0;
        }
        else
        {
            holder->list[commandC] = calloc(strlen(token) + 1, sizeof(char));
            strcpy(holder->list[commandC], token);
            commandC++;
            holder->noInput = 1;
        }
        
        if(holder->noInput == 1)
        {
            while((token = strtok_r(NULL, " ", &save)))
            {
                counter += strlen(token);
                /*
                    Compare the tokens with  '<' and '>' signs.
                    If these signs exist, set inputFlag/ outputFlag to 0. These then will be 
                    used to detect the filenames that come after these signs. 

                    char *list also won't take in any '<' or '>' or '&' or any filenames 
                    as they will be processed using execvp. Instead, if there exists a file 
                    input or output or &, make sure to put the file name inside input.txt,
                    output.txt, or change isImpersand to 1 (as it's a flag).
                */

                if(strcmp(token, "<") == 0)
                {
                    inputFlag = 1;
                }
                else if(strcmp(token, ">") == 0)
                {
                    outputFlag = 1;
                }
                else if(strcmp(token, "&") == 0 && counter == lenOfArgument)
                {
                    // if it's only foreground, don't let the program
                    // run the command in the background! 
                    if(onlyForeground == 1)
                    {
                        isForeground = 1;
                        isBackground = 0;
                        holder->isAmpersand = 1;
                    }
                }
                else
                {
                    /*
                        Instead of parsing the data of inputFile and outputFile name in the
                        char* list[maxArguments], we parse those data separately. This way 
                        execvp will work when list is passed into it! 
                    */
                    if(inputFlag == 1)
                    {
                        holder->inputF = calloc(sizeof(token) + 1, sizeof(char));
                        strcpy(holder->inputF, token);
                        holder->isInputF = 1;
                        inputFlag = 0;
                    }
                    else if(outputFlag == 1)
                    {
                        holder->outputF = calloc(sizeof(token) + 1, sizeof(char));
                        strcpy(holder->outputF, token);
                        holder->isOutputF = 1;
                        outputFlag = 0;
                    }
                    else
                    {
                        counter++;
                        holder->list[commandC] = calloc(strlen(token) + 1, sizeof(char));
                        strcpy(holder->list[commandC], token);
                        commandC++;
                    }
                }
            }
            holder->commandCounter = commandC;
            holder->list[commandC] = NULL;
        }
    }
    return holder;
}


/*
    handle_SIGTSTP:

    Handle the Ctrl + Z trigger. Whenever the user clicked Ctrl + Z, 
    only let them run their commands in foreground mode. If the key is triggered
    again when the user is already in foreground mode, escape  the foreground mode.
*/
void handle_SIGTSTP(int signo)
{
    char *enterM = "\nEntering foreground-only mode (& is now ignored)\n";
    char *exitM = "\nExiting foreground-only mode\n";
    char *promptM = ": ";

    if(onlyForeground != 0)
    {
        write(STDOUT_FILENO, enterM, 50);
        write(STDOUT_FILENO, promptM, 2);
        onlyForeground = 0;
    }
    else
    {
        write(STDOUT_FILENO, exitM, 30);
        write(STDOUT_FILENO, promptM, 2);
        onlyForeground = 1;
    }
}

/*
    changeDir():
    change the directory. see if input is more than 1, if so, 
    there must be a path that they specified. Try to go into that path, 
    and if it fails, rreturn a perror().
*/
void changeDir(struct input *holder)
{
    if(holder->commandCounter > 1)
    {
        if(chdir(holder->list[1]) != 0)
        {
            perror("chdir failed!\n");
        }
    }
    // if commandCounter is one, then the user did not
    // specify which path they want to go to.
    else if(holder->commandCounter == 1)
    {
        if(chdir(getenv("HOME")) != 0)
        {
            perror("chdir failed!\n");
        }
    }
}

/*
    statusFunc():
        print the exit status or if the process was terminated, 
        print the signal it was terminated by.
*/
void statusFunc()
{
    /*
        since only one of WIFEXITED or WIFSIGNALED return true, 
        turn it into an if-else statement, and print out if 
        any of the statements evaluate to true.
    */
    if(WIFEXITED(childStatus))
    {
        printf("exit value %d\n", WEXITSTATUS(childStatus));
        fflush(stdout);

    }
    else if(WIFSIGNALED(childStatus))
    {
        printf("terminated by signal %d\n", WTERMSIG(childStatus));
        fflush(stdout);
    }
}

/*
    checking if any of the child processes became a zombie and can be reaped.
    Citation: 
       The lecture Process API - Monitoring Child Processes helped me understand 
       the concept about checking child processes. 
*/
void checkIfProcessesFinish(int cpid)
{
    pid_t holder;
    pid_t backProcess = getpid();


    holder = waitpid(-1, &childStatus, WNOHANG);
    while(holder > 0)
    {
        printf("background pid %d is done: ", backProcess);
        fflush(stdout);

        statusFunc();
        holder = waitpid(-1, &childStatus, WNOHANG);
    }
}

/*
    Citation: 
        The lecture Processes and I/O helped in creating this function. 
        dup2() and how we could redirect the stdin and stdout was also
        learnt from that lecture.
*/
void executeCommand(struct input *holder, char *args)
{
    
    int redirectIn;
    int redirectOut;

    // check if this is a foreground process, if it is then set the sigint to default.
    if(isForeground == 0)
    {
        SIGINT_action.sa_handler = SIG_DFL;
        sigaction(SIGINT, &SIGINT_action, NULL);
    }

    //INPUT REDIRECTION
    if(holder->isInputF == 1)
    {
        int sourceFile;
        if(isBackground == 0)
        {
            sourceFile = open(backRedirection, O_RDONLY);
            if(sourceFile == -1)
            {
                printf("cannot open %s for input\n", holder->inputF);
                fflush(stdout);
                exit(1);
            }
        }
        else
        {
            sourceFile = open((holder->inputF), O_RDONLY);
            if(sourceFile == -1)
            {
                printf("cannot open %s for input\n", holder->inputF);
                fflush(stdout);
                exit(1);
            }
        }
        // redirect stdin to source file!
        redirectIn = dup2(sourceFile, 0);
        if(redirectIn == -1)
        {
            printf("dup () error\n");
            fflush(stdout);
            exit(2);
        }
    }

    // OUTPUT REDIRECTION
    if(holder->isOutputF == 1)
    {
        int targetFile;
        if(isBackground == 0)
        {
            targetFile = open(backRedirection, O_WRONLY);
            if(targetFile == -1)
            {
                printf("cannot open %s for output\n", holder->inputF);
                fflush(stdout);
                exit(1);
            }
        }
        else
        {
            targetFile = open((holder->outputF), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(targetFile == -1)
            {
                printf("cannot open %s for output\n", holder->inputF);
                fflush(stdout);
                exit(1);
            }
        }

        redirectOut = dup2(targetFile, 1);
        if(redirectOut == -1)
        {
            printf("dup () error\n");
            fflush(stdout);
            exit(2);
        }
    }

   if(execvp(holder->list[0], holder->list) == -1)
   {
       printf("%s: no such file or directory\n", holder->list[0]);
       exit(1);
   }
}

/*
    Citation: Monitoring Child Processes really helped in inspiring me to make this 
    function. The code example included in that lecture especially.
*/ 
void forkFunc(struct input *list, char *args)
{
    pid_t pidHolder;
    pid_t cpid;
    
    pidHolder = fork();

    switch(pidHolder)
    {
        case -1:
            perror("fork() failed");
            exit(1);
            break;
        case 0:
            cpid = getpid();
            
            if(isBackground == 0 || isForeground == 1)
            {
                // keep a track of background num processes.
                backgroundPid[countBackPid] = cpid;
                countBackPid++;
            }
            // check if any background processes has terminated 

            executeCommand(list, args);
        default:
            if(isForeground == 0)
            {
                // wait for child process to end before returning to 
                // reprompt.
                waitpid(-1, &childStatus, 0);
                if(WIFSIGNALED(childStatus))
                {
                    printf("terminated by signal %d\n", WTERMSIG(childStatus));
                    fflush(stdout);
                }
            }
            else if(isForeground != 0 )
            {
                // as this is background, do not kill any of the child processes and
                // just move on.
                printf("background pid is %d\n", getpid());
                fflush(stdout);
            }
            break;
    }

    checkIfProcessesFinish(getpid());
}


/*
    exitFunc():
    clean up all the processes and exit the program.
*/
void exitFunc()
{
    if(countBackPid != 0)
    {
        for(int i = 0; i < countBackPid; i++)
        {
            kill(backgroundPid[i], SIGTERM);
        }
    }
    else
    {
        exit(0);
    }
    exit(0);
}

/*
    Any built-in commands will be executed in this function (so they will also be done in foreground).
    Pass any other commands to the forkFunction. 
*/
void runCommand(struct input *holder, char *args, int* signalH)
{
    // check if holder->noInput == 0 
    if(holder->noInput == 0)
    {
        // do not do anything since it means that the string is empty. 
    }
    else if(holder->noInput == 1)
    {
        if(strcmp(holder->list[0], "cd") == 0)
        {
            changeDir(holder);
        }
        else if(strcmp(holder->list[0], "exit") == 0)
        {
            exitFunc();
        }
        else if(strcmp(holder->list[0], "status") == 0)
        {
            statusFunc();
        }
        /*
             use excvp() for any other commands. run them in the foreground/background.
        */
        else 
        {
            forkFunc(holder, args);
        }
    }
}

/*
    compareChar, see if char is the same, 
    if it is return 0.
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
    changeList(): changes any instances of $$ in a string into the pid number!
*/
void changeList(char *args, int stop, char *pid, int *var)
{
    //printf("Hello1\n");
    char holder[maxArguments] = "";
    int length = strlen(args);
    int pidL = strlen(pid);
    int count = 0;

    // copy the first few characters before '$'
    for(int i = 0; i < stop; i++)
    {
        holder[i] = args[i];
    }
    
    // concatenate the pid to holder.
    strcat(holder, pid);

    // set lenStart to where stop was + 6.
    int lenStart = pidL + stop;

    // start where args[i] was left off and keep on 
    // copying to the holder array.
    for(int i = stop + 2; i < length - 1; i++)
    {   
        //printf("Hello\n");
        holder[lenStart] = args[i];
        lenStart++;
        count++;
    }
    
    // copy holder to args!
    *var = count;
    strcpy(args, holder);
}


/*
    searchForSign() : searches for the # sign in a string. If args[0] == #, then return 0.
    If else, return 1.

    Why this method was chosen: the char *args was passed to this function so that checking
    will be more efficient and easier.
*/
int searchForSign(char *args)
{
    int lenOfArg = strlen(args);

    for(int i = 0; i < lenOfArg; i++)
    {
        if(compareChar(args[i], '#') == 0 && i == 0)
        {
            return 0;
        }
    }
    return 1;
}

/*
    goThroughList: goes through the list and check if there's any instances of $. if so,
    pass it to changeList so that the string can be manipulated with the pid() number.
*/
void goThroughList(char *args)
{
    int noVariables = 0;
    char tmp[maxArguments];
    strcpy(tmp, args);

    int lenOfArg = strlen(args);
    char pidHolder[5];

    for(int i = 0; i < lenOfArg; i++)
    {
        if(compareChar(args[i], '$') == 0)
        {
            if(compareChar(args[i+1], '$') == 0)
            {
                sprintf(pidHolder, "%d", getpid());
                changeList(args, i, pidHolder, &noVariables);
                i+=4;
                lenOfArg = strlen(args);
            }
        }
    }
}

/*
    Reset() function: 
    Reset the values of the program for new prompt.
*/
void reset(struct input *holder, char *args)
{
    if(holder->noInput == 0)
    {
        holder->noInput = 0;
    }
    else if(holder->noInput == 1)
    {
        if(holder->commandCounter > 0)
        {
            for(int i = 0; i < holder->commandCounter; i++)
            {
                free(holder->list[i]);
            }
            holder->commandCounter = 0;
        }
        if(holder->isInputF == 1)
        {
            free(holder->inputF);
            holder->isInputF = 0;
        }
        if(holder->isOutputF == 1)
        {
            free(holder->outputF);
            holder->isOutputF = 0;
        }
        holder->noInput = 0;
    }
    
    if(onlyForeground != 0)
    {
        isForeground = 0;
        isBackground = 1;
    }
    strcpy(args, "");
}

void handle_SIGCHLD(int sig)
{
    pid_t holder;
    int loopAgain = 0;

    while(loopAgain == 0)
    {
        if(countBackPid > 0)
        {
            holder = waitpid(-1, &childStatus, WNOHANG);

            if(holder <= 0)
            {
                printf("background pid %d is done:", holder);
                fflush(stdout);

                if(WIFEXITED(childStatus) == 0)
                {
                    printf("exit value %d\n", WEXITSTATUS(childStatus));
                    fflush(stdout);

                }
                else if(WIFSIGNALED(childStatus) == 0)
                {
                    printf("handler\n");
                    printf("terminated by signal %d\n", WTERMSIG(childStatus));
                    fflush(stdout);
                }
                loopAgain = 1;
            }
        }
        else
        {
            loopAgain = 1;
        }
    }
}

int main()
{
    char inputFromCommand[maxArguments];
    char cwd[maxArguments];
    int inputLoop = 0;
    struct input *inputH;
    int signalHolder;
    int debug = 1;

    // get the starting directory with getcwd()
    if(getcwd(cwd,sizeof(cwd)) != NULL)
    {
        startDir = cwd;
    }
    
    SIGINT_action.sa_handler = SIG_IGN;
    SIGINT_action.sa_flags = SA_RESTART;
    sigfillset(&SIGINT_action.sa_mask);
    sigaction(SIGINT, &SIGINT_action, NULL);

    // SIGSTP_action calls the sigstp handler which prints out 
    // the message to the screen. 
    SIGTSTP_action.sa_handler = handle_SIGTSTP;
    SIGTSTP_action.sa_flags = SA_RESTART;
    sigfillset(&SIGTSTP_action.sa_mask);
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);

    signal(SIGCHLD, handle_SIGCHLD);

    while(inputLoop == 0)
    {
        signalHolder = 0;

        // check if any child processes are done and clean them up! 
        checkIfProcessesFinish(getpid());

        // asks for input from user and parse the data.
        inputH = getInput(inputFromCommand);

        /* 
              For testing to see if we parsed the document right: 
        */
        
        if(debug == 0)
        {
            printf("%d\n", inputH->commandCounter);

            for(int i = 0; i < inputH->commandCounter; i++)
            {
                printf("%s\n", inputH->list[i]);
            }
            printf("%d\n", inputH->noInput);
            printf("%d\n", inputH->isOutputF);
            printf("%d\n", inputH->isInputF);
        }

       // as long as input is not 0, run command. We use inputH->noInput
       // as a flag so that when user enters # or a blank line command, 
       // our program can just skip over them and prompt for a new input.
       if(inputH->noInput != 0)
       {
            runCommand(inputH, inputFromCommand, &signalHolder);
            reset(inputH, inputFromCommand);
       }
    }
}