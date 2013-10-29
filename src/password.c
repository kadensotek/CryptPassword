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

    programLoop();

    printf("Thank you and have a nice day.\n\n");
    return 0;
}

void programLoop()
{
    int quit = 0;
    int choice = 0;
    FILE *fp = NULL;
    char filename[] = "userpass.txt";
    srand(time(0));

    fp = fopen(filename, "r");

    if(fp = NULL)
    {
        fp = fopen(filename, "w+");
    }
    else
    {
        fclose(fp);
    }

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
                    addUser(filename);
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

void addUser(char *filename)
{
    FILE *fp;
    char salt[3] = "";
    char *username = malloc(11);
    char *password = malloc(11);
    char *hashpass = malloc(14);
    int userExists = 0;

    /* gets random seed for hashing */
    salt[0] = randomChar();;
    salt[1] = randomChar();
    salt[2] = '\0';

    fprintf(stdout, "\nPlease enter a username to add (limited to 10 characters)\n>  ");
   
    username = getInput(username, 11);

    userExists = findMatch(filename, username);    

    if(userExists == -1)
    {
        fprintf(stdout, "\n\tError: \"%s\" file not found.\n", filename);

        return;
    } 
    else if(userExists == 1)
    {
        fprintf(stdout, "\n\tError: user \"%s\" already exists\n", username);
        return;
    }
    else
    {
        fprintf(stdout, "\nPlease enter your password (limited to 10 characters)\n>  ");
        password = getInput(password, 11);

        hashpass = crypt(password, salt);

        if(hashpass == NULL)
        {
            fprintf(stdout, "\n\tError: password hash creation failed.\n");
            return;
        }
        else
        {
            if((fp = fopen(filename, "a")) == NULL)
            {
                fprintf(stdout, "\n\tError: can't write to file \"%s\".\n", filename);
                return;
            }
            else
            {
               fprintf(fp, "%s %s\n", username, hashpass); 
            }

            fclose(fp);
        }

        fprintf(stdout, "\n\tAdded user \"%s\"\n", username);
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
