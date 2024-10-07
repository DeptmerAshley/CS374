#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Movie {
    int year;
    float rating;
    char title[100];
    char languages[100];

    struct Movie *next;
} Movie;

struct Movie *head = NULL;

void read(const char* fname) {
    FILE *movies = fopen(fname, "r"); //change arg 1 to fname later
    if (!movies) {
        printf("Error: File not found/Cannot open\n");
        return;
    }

    struct Movie *current = NULL;
    char line[250];

    if (fgets(line, sizeof(line), movies) == NULL) {
        fclose(movies);
        return;
    }
    int num_movies = 0;

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
                            current -> next = movie_obj;
                            current = movie_obj;
                        }
                    }
                }
            }
        }
    }
    printf("\nThe file given has been processed %s and parsed %d movies\n\n", movies, num_movies);
}

void menu() {
    printf("_______________________________________________________________________________\n");
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    printf("\nPlease enter your selection: ");

}

int main(int argc, char* argv[]) {

    if(argc!= 2) {
        printf("Usage: %s <fname>\n", argv[0]);
        return 1;
    }

    menu();
    read(argv[1]);

    
}

