#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main ()
{
    srand(time(NULL) * getpid());

    int dirNumberTail = rand() % 99999;
    char dnt[6];
    char fileHead[25] = "ashledep.movies.";
    itoa(dirNumberTail, dnt, 10);
    strcat(fileHead, dnt);

    printf("%s", fileHead);
    if (mkdir("ashledep.movies.1972") == -1) 
    {
        perror("\nError");

    }

    return 0;
}