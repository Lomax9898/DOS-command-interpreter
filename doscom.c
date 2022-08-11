#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include<unistd.h>
#define MAX 100
bool volatile loop = true;

void intHandler(int example) //This is for the CTRL-C catcher
{
    loop = false;
    exit(0);
}


int main ()
{
    char input[50];
    char command[100];
    char s[100];
    char string[200];
    char arg1[50];
    char arg2[50];
    int length;
    int count=0;
    char delim[] = " ";


    while(loop == true)
    {
        fgets(input,  MAX, stdin);
        char *ptr = strtok(input, delim);
        while (ptr != NULL) // This is how I find out if there are arguments
        {
            // Then I split input into tokens
            count++;
            if(count == 1)
            {
                strcpy(command, ptr);
            }
            else if(count == 2)
            {
                strcpy(arg1, ptr);
            }
            else if(count == 3)
            {
                strcpy(arg2, ptr);
            }
            ptr = strtok(NULL, delim);
        }
        count = 0;
        signal(SIGINT, intHandler); // This catches a control-c input
        length = strlen(command);
        if (command[length-1] == '\n')
        {
            command[length-1] = '\0';
        }
        if(strcmp("dir", command)== 0) // Majority of the code is checking for NULL
        {
            getcwd(s, 100); // Gets the path name of current directory
            sprintf(string,"ls %s",s);
            system(string);
        }
        else if(strcmp("type", command)== 0)
        {
            if(arg1[0] != '\0')
            {
                length = strlen(arg1);
                if (arg1[length-1] == '\n')
                {
                    arg1[length-1] = '\0';
                }
                length = strlen(arg2);
                if(arg2[0] != '\0')
                {
                    if (arg2[length-1] == '\n')
                    {
                        arg2[length-1] = '\0';
                    }
                    sprintf(string,"cat %s %s",arg1, arg2);
                    system(string);
                }
                else
                {
                    sprintf(string,"cat %s",arg1);
                    system(string);
                }
            }
        }
        else if(strcmp("cd", command)== 0)
        {
            if(arg1[0] != '\0')
            {
                length = strlen(arg1);
                if (arg1[length-1] == '\n')
                {
                    arg1[length-1] = '\0';
                }
                chdir(arg1);  // Changes the current directory to arg1
            }
            else
            {
                chdir(".."); // This makes cd command go back a step in file path
            }                // home/test/folder > home/test/
        }
        else if(strcmp("del", command)== 0)
        {
            if(arg1[0] != '\0')
            {
                length = strlen(arg1);
                if (arg1[length-1] == '\n')
                {
                    arg1[length-1] = '\0';
                }
                sprintf(string,"rm %s",arg1);
                system(string);
            }
            else
            {
                strcpy(command,"rm"); // The purpose of this is let the error message show
                system(command);      // for invalid input
            }
        }
        else if(strcmp("ren", command)== 0)
        {
            if(arg1[0] != '\0' && arg2[0] != '\0')
            {
                length = strlen(arg1);
                if (arg1[length-1] == '\n')
                {
                    arg1[length-1] = '\0';
                }
                length = strlen(arg2);
                if (arg2[length-1] == '\n')
                {
                    arg2[length-1] = '\0';
                }
                sprintf(string,"mv %s %s",arg1,arg2);
                system(string);
            }
            else
            {
                strcpy(command,"mv");
                system(command);
            }
        }
        else if(strcmp("copy", command)== 0)
        {
            if(arg1[0] != '\0' && arg2[0] != '\0')
            {
                length = strlen(arg1);
                if (arg1[length-1] == '\n')
                {
                    arg1[length-1] = '\0';
                }
                length = strlen(arg2);
                if (arg2[length-1] == '\n')
                {
                    arg2[length-1] = '\0';
                }
                sprintf(string,"cp %s %s",arg1,arg2);
                system(string);
            }
            else
            {
                strcpy(command,"cp");
                system(command);
            }
        }
        else
        {
            system(command);
        }
        memset(command, 0, 100); // Set everything back to zero for the loop
        memset(arg1, 0, 50);
        memset(arg2, 0, 50);
        memset(string, 0, 200);
        printf("\nType Ctrl-C to exit.\n");
    }
    return(0);
}
