#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct Movie {
    int year;
    float rating;
    char title[100];
    char languages[100];

    struct Movie *next;
} Movie;

//Global Variable for the head of the linked list
struct Movie *head = NULL;

//Function that opens the file when the program is launched
void parse(char* fname[]) {
    printf("==========================");
    FILE *movies = fopen(*fname, "r");
    if (!movies) {
        printf("Error: File not found/Cannot open\n");
        return;
    }

    struct Movie *current = NULL;
    char line[250];

    //Skip the first line with column names
    if (fgets(line, sizeof(line), movies) == NULL) {
        fclose(movies);
        return;
    }
    int num_movies = 0;

    //Iterate through the file lines and populate Movie structures into a linked list
    while(fgets(line, sizeof(line), movies) != NULL) {
        num_movies++;
        struct Movie *movie_obj = malloc(sizeof(struct Movie));
        char *token = strtok(line, ",");
        if (token) {
            strcpy(movie_obj->title, token);
            token = strtok(NULL, ",");

            if (token) {
                movie_obj->year = atoi(token);
                token = strtok(NULL, ",");

                if (token) {
                    strcpy(movie_obj->languages, token);
                    token = strtok(NULL, ",");

                    if (token) {
                        movie_obj->rating = atof(token);
                        movie_obj->next = NULL;

                        if (head == NULL) {
                            head = movie_obj;
                            current = movie_obj;
                        }
                        else {
                            current->next = movie_obj;
                            current = movie_obj;
                        }
                    }
                }
            }
        }
    }
    printf("\nThe file given has been processed %s and parsed %d movies\n\n", fname, num_movies);
}



void newMovieDirectory() 
{
    int dirNumberTail = rand() % 99999;
    char dnt[6];
    char fileHead[25] = "ashledep.movies.";
    itoa(dirNumberTail, dnt, 10);
    strcat(fileHead, dnt);
    if (mkdir(fileHead) == -1) 
    {
        perror("Error");
    }
    //movieFileSep();
}

// void movieFileSep() 
// {
    
// }
void largestFile();
void smallestFile();



void menu() {
    printf("\n_______________________________________________________________________________\n\n");
    printf("1. Select file to process\n");
    printf("2. Exit the program\n");
    printf("\nPlease enter your selection: ");
}

void menuTwo() {
    printf("\n_______________________________________________________________________________\n\n");
    printf("1. Select largest file\n");
    printf("2. Select smallest file\n");
    printf("3. Specify the name of a file\n");
    printf("\nPlease enter your selection: ");
}

int main() 
{
    srand(time(NULL) * getpid());
    int userComplete = 1;
    int input;
    do {
        menu();
        int menuSelection;

        scanf("%d", &input);

        while(input > 2 || input < 1) 
        {
            printf("Please enter a valid integer: ");
            scanf("%d", &input);
        }

        if (input == 2) 
        {
            printf("\n\nShutting down........\n\n");
            userComplete = 0;
            break;
        }
        else if (input == 1) 
        {
            menuTwo();
            scanf("%d", &input);
            while(input > 3 || input < 1) 
            {
                printf("Please enter a valid integer: ");
                scanf("%d", &input);
            }

            if (input == 1)
            {
                //largestFile();
            }
            else if (input == 2)
            {
                //smallestFile();
            }
            else if (input == 3)
            {
                char* fname[50];
                printf("Please enter a filename: ");
                scanf("%s", fname);
                parse(fname);
                newMovieDirectory();
            }
            

        }
    } while (userComplete = 1);

    return 0;
}
