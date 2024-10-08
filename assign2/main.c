#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int main() {

    int userComplete = 1;
    int input;
    do {
        menu();
        int menuSelection;

        scanf("%d", &input);

        while(input > 2 || input < 1) {
            printf("Please enter a valid integer: ");
            scanf("%d", &input);
        }

        if (input == 2) {
            printf("\n\nShutting down........\n\n");
            userComplete = 0;
            break;
        }
        else if (input == 1) {
            menuTwo();
            while(input > 2 || input < 1) {
                printf("Please enter a valid integer: ");
                scanf("%d", &input);
            }
        }
    } while (userComplete = 1);

    return 0;
}
