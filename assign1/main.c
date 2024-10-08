#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Movie structure with attached linked list
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
void read(const char* fname) {
    FILE *movies = fopen(fname, "r"); //change arg 1 to fname later
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


//Menu function
void menu() {
    printf("\n_______________________________________________________________________________\n\n");
    printf("1. Show movies released in the specified year\n");
    printf("2. Show highest rated movie for each year\n");
    printf("3. Show the title and year of release of all movies in a specific language\n");
    printf("4. Exit from the program\n");
    printf("\nPlease enter your selection: ");

}

//Function for movies in selected years
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


//A simplie print function
void print(struct Movie *temp)
{
    printf("  %d", temp->year);
    printf("  %.1f", temp->rating);
    printf("  %s", temp->title);
    printf("\n");
}


//splits the linked list into two parts
void split(struct Movie *start, struct Movie **front, struct Movie **back) {
    struct Movie *slow = start;
    struct Movie *fast = start->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = start;
    *back = slow->next;
    slow->next = NULL;
}

struct Movie* sortMerge(struct Movie* first, struct Movie* second ){
    struct Movie* answer = NULL;

    if (first == NULL){
        return (second);
    }
    if (second == NULL){
        return (first);
    }

    if (first->year <= second->year){
        answer = first;
        answer->next = sortMerge(first->next, second);
    }
    else{
        answer = second;
        answer->next = sortMerge(first, second->next);
    }

    return (answer);
}

//Algorithm for finding movies with the highest rating in each year
void mergeSort(struct Movie** headTemp){
    struct Movie* head = *headTemp;
    struct Movie* first;
    struct Movie* second;

    if ((head == NULL) || (head->next == NULL)){
        return;
    }
    //Calls split to split the list into smaller lists
    split(head, &first, &second);
    //Recursivly calls the function with the first and second list
    mergeSort(&first);
    mergeSort(&second);
    //Sort merge then merges the lists back togeather
    *headTemp = sortMerge(first, second);

}

void highPerYear() {
//First merge sort is called to make the list oder from earlist to latest year    
    mergeSort(&head);
    
    struct Movie *p = head;
    int tempYear = p->year;
    struct Movie *temp = p;
    double highRate = p->rating;
    //This loop will go through the list comparing the year of last interation to current
    //If the year is differnt it prints the data foright rated movie
    while (p != NULL) {
        if (p->year != tempYear) {
            print(temp);
            highRate = p->rating;
            temp = p;
            tempYear = p->year;
        } 
        else if (p->rating > highRate) {
            highRate = p->rating;
            temp = p;
        }
        p = p->next;
    }
    print(temp);
}

//Function to cut strings in order to find the correct language
char* stringCut(char* str) {
    while (*str == ' ') {
        str++;
    }
    char* end = str + strlen(str) - 1;
    while (end > str && *end == ' ') {
        end--;
    }

    end[1] = '\0';
    return str;
}

//Function that finds movie with selected languages
struct Movie* searchLang(struct Movie *movies, const char *language) {
    int found = 0;
    while (movies != NULL) {
        char tempLanguages[100];
        strcpy(tempLanguages, movies->languages);
        char *start = strchr(tempLanguages, '[');
        char *end = strchr(tempLanguages, ']');
        if (start && end) {
            memmove(start, start + 1, end - start);
            start[end - start - 1] = '\0';
        }

        char *token = strtok(tempLanguages, ";"); 
        
        while (token != NULL) {
            char* stringCutLanguage = stringCut(token); 
            // Use strcasecmp to handle case insensitivity
            //if languages match it will then print the needed information
            if (strcasecmp(language, stringCutLanguage) == 0) {
                printf("\n  %d", movies->year);
                printf("  %s", movies->title);
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


//Function for user input on which language to search for
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

