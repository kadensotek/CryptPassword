#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <crypt.h>

void programLoop();
void printMainMenu();
void addUser(char *filename);
void deleteUser(char *filename);
void authenticate(char *filename);
char randomChar();
char *getInput(char *input, int size);

int main(int argc, char *argv[])
{
    printf("Welcome to the User Management System.\n");

    srand(time(0));

    programLoop();

    printf("Thank you and have a nice day.\n\n");

    return 0;
}

void programLoop()
{
    int quit = 0;
    int choice = 0;

    while(!quit)
    {
        printMainMenu();

        choice = getchar()-48;  /* adjusts ascii to integer */

        while(getchar() != '\n') /* strips all but first char  */
        {
            ;
        }

        printf("\n");

        switch(choice)
        {
            case 1:
                    printf("Adding user\n");
                    //addUser(filename);
                    break;
            case 2:
                    printf("Deleting user\n");
                    //deleteUser(filename);
                    break;
            case 3:
                    printf("Authenticating user\n");
                    //authenticate(filename);
                    break;
            case 0:
                    quit = 1;
                    break;
            default:
                    printf("\tThat's not an option.  Please choose again.\n");
        }
    }
}

void printMainMenu()
{
    printf("\nMain Menu\n");
    printf("############\n");
    printf("1. Add user.\n");
    printf("2. Delete user.\n");
    printf("3. Authenticate user.\n");
    printf("0. Exit.\n");
    printf("Please enter a number to make a selection.\n");
    printf("> ");
}

char randomChar()
/* called when creating salt for password hash creation  */
{
    char saltChars[] = ".abcdefghijklmnopqrstuvwxyz12345"
                       "/ABCDEFGHIJKLMNOPQRSTUVWXYZ67890";
    char myChar = '0';
    int index = rand();
    index = index%64;   /* makes index 0-63 for saltChars array */

    myChar = saltChars[index];

    return myChar;
}

char *getInput(char *input, int size)
/* gets input from user while clearing buffer and stripping newline chars */
{
    int i =0;

    /* loops until EOF or newline char is reached */
    for ( ;;)
    {
        int ch = fgetc(stdin);

        if(ch=='\n' || ch==EOF)
        {
            break;
        }

        if(i<size-1) /* only stores char if within size limit */
        {
            input[i++] = ch;
        }
    }

    input[i] = '\0'; /* appends null terminator wherever loop is broken  */

    return input;
}
