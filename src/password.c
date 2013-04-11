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
