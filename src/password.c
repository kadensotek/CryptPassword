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

int main(int argc, char *argv[])
{
    printf("Welcome to the User Management System.\n");

    programLoop();

    return 0;
}

void programLoop()
{
    printMainMenu();
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

    mychar = saltChars[index];

    return myChar;
}
