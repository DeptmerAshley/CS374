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
    printf("\n_______________________________________________________________________________\n\n");
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
            while (current != NULL) {
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
    for (int year = 1900; year <= 2021; year++) {
        struct Movie *hold = malloc(10*sizeof(Movie));
        char highestRatingTitle[100] = "";
        float highestRating = 0.0;
        int i = 0;
        struct Movie *current = head;
        while (current != NULL) {
            if (current->year == year) {
                hold[i] = *current;
                i++;
            }
            current = current->next;
        }
        highestRating = hold[0].rating;
        for (int j = 0; j <= i; j++) {
            if (hold[j].rating > highestRating) {
                strcpy(highestRatingTitle, hold[j].title); 
                highestRating = hold[j].rating;
            }
            else if (i == 1){
                strcpy(highestRatingTitle, hold[0].title); 
                highestRating = hold[0].rating;
            }
        }
        if (highestRating == 0.0) {
            continue;
        }
        else {
            printf("\n%d: %s - %f", year, highestRatingTitle, highestRating);
        }
        free(hold);
        hold = NULL;
    }
}

char* stringCut(char* str) {
    while (*str == ' ') {
        str++;
    }
    char* end = str + strlen(str) - 1;
    while (end > str && *end == ' ') {
        end--;
    }
    //returns the trimmed string
    end[1] = '\0';
    return str;
}

struct Movie* searchLang(struct Movie *movies, const char *language) {
    int found = 0;
    while (movies != NULL) {
        char temp_languages[100];
        strcpy(temp_languages, movies->languages);
//This part looks for the start and end bracket then comparing the token to choosen language
        char *start = strchr(temp_languages, '[');
        char *end = strchr(temp_languages, ']');
        if (start && end) {
            memmove(start, start + 1, end - start);
            start[end - start - 1] = '\0';
        }

        char *token = strtok(temp_languages, ";"); 
        
        while (token != NULL) {
            char* stringCutLanguage = stringCut(token); 
            // Use strcasecmp to handle case insensitivity
            //if languages match it will then print the needed information
            if (strcasecmp(language, stringCutLanguage) == 0) {
                printf("\n  %d", movies->year);
                printf("\n  %s", movies->title);
                printf("\n");
                found = 1;
                break;
            }
            token = strtok(NULL, ";");
        }
        movies = movies->next;
    }
    
    if (found == 0) {
        printf("No movies found matching the language: %s\n", language);
    }
    
    return NULL;
}



void showMovieLang(){
    struct Movie *movies = head;
    char language[20];
    printf("Please enter the move language you wish to search for: ");
    scanf("%s",language);
    searchLang(movies, language);
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

        while(input > 4 || input < 1) {
            printf("Please enter a valid integer: ");
            scanf("%d", &input);
        }

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
        else if (input == 3) {
            showMovieLang();
        }


    } while (userComplete = 1);

    return 0;
}

