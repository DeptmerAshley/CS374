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

void menu() {
    printf("_______________________________________________________________________________\n");
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    printf("\nPlease enter your selection: ");

}

void moviesInYear() {
    struct Movie *current = head;
    int yearSelection;
    printf("Please enter a year between 1900 and 2021: ");
    if (scanf("%d", &yearSelection) == 1) {
        if (yearSelection >= 1990 && yearSelection <= 2021) {
            printf("\n%d: ", yearSelection);
            while (current->next != NULL) {
                if (current->year == yearSelection) {
                    printf("%s, ", current->title);
                }
                current = current->next;
            }
            printf("\n");
        }
        else {
            printf("Please select a year between 1900 and 2021.\n");
        }
    }
    else {
        printf("Please enter a valid integer");
        while (getchar() != '\n');
    }
}

void highPerYear() {
    struct Movie * current = head;
    for (int year = 1900; year <= 2021; year++) {
        
    }
}


int main(int argc, char* argv[]) {

    if(argc!= 2) {
        printf("Usage: %s <fname>\n", argv[0]);
        return 1;
    }
    read(argv[1]);

    int userComplete = 1;
    int input;
    do {
        menu();
        int menuSelection;

        scanf("%d", &input);

        if (input == 4) {
            printf("\n\nShutting down........\n\n");
            userComplete = 0;
            break;
        }
        else if (input == 1) {
            moviesInYear();
        }
        else if (input == 2) {
            highPerYear();
        }


    } while (userComplete = 1);

    return 0;
}

