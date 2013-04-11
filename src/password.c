#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <crypt.h>

void printMainMenu();
void addUser(char *filename);
void deleteUser(char *filename);
void authenticate(char *filename);

int main(int argc, char *argv[])
{
    printf("Hello, world!\n");

    return 0;
}

void printMainMenu()
{
    printf("1. Add user.\n");
    printf("2. Delete user.\n");
    printf("3. Authenticate user.\n");
    printf("0. Exit.\n");
    printf("Please enter a number to make a selection.\n");
    printf("> ");
}
