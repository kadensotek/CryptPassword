#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

void programLoop();
void printMainMenu(); 
void addUser(char *filename);
void deleteUser(char *filename);
void authenticate(char *filename);
char randomChar();
char *getInput(char *input, int size);
int findMatch(char *filename, char *username);

int main()
{
    fprintf(stdout, "Welcome to the SJFC system.\n");
    programLoop();
    fprintf(stdout, "\tThank you and have a nice day.\n\n");
}

void programLoop()
{
    FILE *fp = NULL;
    int quit = 0;
    int choice = 9;
    char filename[] = "userpass.txt";

    srand(time(0));   

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        fp = fopen(filename, "w+");  
        fclose(fp);
    }
    else
    {
        fclose(fp);
    }

    while(!quit)
    {
        printMainMenu();

        choice = getchar() - 48;     

        while(getchar() != '\n')     
        {
            ;
        }

        fprintf(stdout, "\n");

        switch(choice)
        {
            case 1:
               addUser(filename);
               break;
            case 2:
               deleteUser(filename);
               break;
            case 3:
               authenticate(filename);
               break;
            case 0:
               quit = 1;
               break;
            default:
               fprintf(stdout, "\tThat's not an option.  Please choose again.\n");
        }

        fprintf(stdout, "\n");
    }
}

void addUser(char *filename)
{
    FILE *fp;
    char *salt = malloc(3);
    char *username = malloc(11);
    char *password = malloc(11);
    char *hashpass = malloc(14);
    int userExists = 0;

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

void deleteUser(char *filename)
{
    FILE *fp;
    FILE *tempfile;
    char *username = malloc(11);
    char *temp = malloc(20);
    int userExists = 0;

    fprintf(stdout, "\nPlease enter a username to delete (limited to 10 characters)\n>  ");
   
    username = getInput(username, 11);
    userExists = findMatch(filename, username);    
    if(userExists)
    {
        if((fp = fopen(filename, "r")) == NULL)
        {
            fprintf(stdout, "\n\tError: can't read from \"%s\" file.\n", filename);
            free(temp);
            free(username);
            return;
        }

        if((tempfile = fopen("temp.txt", "w")) == NULL)
        {
            fprintf(stdout, "\n\tError: can't write \"temp.txt\" file.\n");
            free(temp);
            free(username);
            return;
        }

        while((fscanf(fp, "%s", temp)) != EOF)
        {
            if(strncmp(username, temp, 11) != 0)
            {
                fprintf(tempfile, "%s ", temp);
                fscanf(fp, "%s", temp);
                fprintf(tempfile, "%s\n", temp);
            }
            else
            {
                fscanf(fp, "%s", temp);
            }
        }

        fclose(fp);
        fclose(tempfile);
        if((fp = fopen(filename, "w")) == NULL)
        {
            fprintf(stdout, "\n\tError: can't write to \"%s\" file.\n", filename);
            free(temp);
            free(username);
            return;
        }

        if((tempfile = fopen("temp.txt", "r")) == NULL)
        {
            fprintf(stdout, "\n\tError: can't read from \"temp.txt\" file.\n");
            free(temp);
            free(username);
            return;
        }

        while((fscanf(tempfile, "%s", temp)) != EOF)
        {
            fprintf(fp, "%s ", temp);
            fscanf(tempfile, "%s", temp);
            fprintf(fp, "%s\n", temp);
        }

        fclose(fp);
        fclose(tempfile);

        if(remove("temp.txt") != 0)
        {
            fprintf(stdout, "\n\tError: could not delete \"temp.txt\".\n");
        }

        fprintf(stdout, "\n\tDeleted user \"%s\"\n", username);
    }
    else
    {
        fprintf(stdout, "\n\tError: user \"%s\" does not exist.\n", username);
    }

    free(temp);
    free(username);
}

void authenticate(char *filename)
{
    FILE *fp;
    char *salt = malloc(3);
    char *username = malloc(11);
    char *storedUsername = malloc(11);
    char *password = malloc(11);
    char *hashpass = malloc(14);
    char *storedHashpass = malloc(14);
    int userExists = 0;

    fprintf(stdout, "\nPlease enter your username (limited to 10 characters)\n>  ");

    username = getInput(username, 11);

    userExists = findMatch(filename, username);    

    if(userExists)
    {
        if((fp = fopen(filename, "r")) == NULL)
        {
            fprintf(stdout, "\n\tError: can't read from \"%s\" file.\n", filename);
            return;
        }
        else
        {
            while((fscanf(fp, "%s", storedUsername)) != EOF)
            {
                if(strncmp(username, storedUsername, 11) != 0)
                {
                    fscanf(fp, "%s", storedHashpass);
                }
                else
                {
                    fscanf(fp, "%s", storedHashpass);
                    break;
                }
            }

            fprintf(stdout, "\nPlease enter your password (limited to 10 characters)\n>  ");
            password = getInput(password, 11);

            salt[0] = storedHashpass[0];
            salt[1] = storedHashpass[1];
            salt[2] = '\0';

            hashpass = crypt(password, salt);

            if(hashpass == NULL)
            {
                fprintf(stdout, "\n\tError: password hash creation failed.\n");
                return;
            }
            else
            {
                int incorrect = 1;
                incorrect = strncmp(hashpass, storedHashpass, 14);

                if(!incorrect)
                {
                    fprintf(stdout, "\n\tAuthentication successful.\n");
                }
                else
                {
                    fprintf(stdout, "\n\tError: password incorrect.\n");
                }
            }
            fclose(fp);

        }
    }
    else
    {
        fprintf(stdout, "\n\tError: user \"%s\" does not exist.\n", username);
    }
}

void printMainMenu()
{
    fprintf(stdout, "1. Add user.\n");
    fprintf(stdout, "2. Delete user.\n");
    fprintf(stdout, "3. Authenticate user.\n");
    fprintf(stdout, "0. Exit.\n");
    fprintf(stdout, "Please enter a number to make a selection.\n");
    fprintf(stdout, "> ");
}

char randomChar()
{
    char saltChars[] = ".abcdefghijklmnopqrstuvwxyz12345"     
                       "/ABCDEFGHIJKLMNOPQRSTUVWXYZ67890";
    char myChar = '0';
    int index = rand();
    index = index%64;                    
    myChar = saltChars[index];

    return myChar;
}

char *getInput(char *input, int size)
{
   int i = 0;

   for ( ;; )
   {
      int ch = fgetc(stdin);
      if ( ch == '\n' || ch == EOF )
      {
         break;
      }
      if ( i < size - 1 )  
      {
         input[i++] = ch;
      }
   }

   input[i] = '\0'; 
   return input;
}

int findMatch(char *filename, char *username)
{
    FILE *fp;
    int resultFound = 0;
    char temp[50];

    if((fp = fopen(filename, "r")) == NULL)
    {
        return(-1);
    }

    while((fscanf(fp, "%s", temp)) != EOF)
    {
        if(strncmp(username, temp, 11) == 0)
        {
            resultFound = 1;
            break;
        }

        fscanf(fp, "%s", temp);
    }

    fclose(fp);

    return(resultFound);
}
