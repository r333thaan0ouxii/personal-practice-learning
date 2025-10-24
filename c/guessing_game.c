#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_STRING
} InputType;

void retry_input(InputType type, void* variable, int (*addCondition)(void *), char* errMessage);

int check_positive(void *value) {
    int val = *(int *)value;
    return val <= 0;
}

int check_yn(void *value) {
    char val = *(char *)value;
    return val != 'y' && val != 'Y' && val != 'n' && val != 'N';
}

int main(void) {
    while (1)
    {
        srand(time(NULL)); // Reset seed every time the program is run

        int max;

        printf("Welcome to a quick guessing game in C!\n");
        printf("I'll choose a number between 1 and a maximum number of your preference, and you'll have to guess it.\n");
        printf("Please choose the maximum range for this number guessing game: ");

        retry_input(
            TYPE_INT,
            &max,
            check_positive,
            "Please enter a number greater than 0, try again: "
        );
        
        char limitedTries;

        printf("Do you want to have limited tries?\n(Y/N):");
        retry_input(
            TYPE_CHAR,
            &limitedTries,
            check_yn,
            "Invalid output, try again:\n(Y/N):"
        );

        int tryAmount = 0;

        if (limitedTries == 'y' || limitedTries == 'Y') {
            printf("Please enter the amount of tries you want to have: ");
            retry_input(
                TYPE_INT,
                &tryAmount,
                check_positive,
                "Please enter a number greater than 0, try again: "
            );
        }

        int randomNumber = (rand() % max) + 1;

        printf("I chose a number between 1 and %d, can you guess it?\n", max);

        int guess;
        int won = 0;
        for (int i = 1; tryAmount == 0 || i <= tryAmount; i++) { //I know I can just do "do" or "while" but I'm lazy, in my eyes seems like a cleaner implementation of an index to keep track of
            printf("Try #%d: ", i);
            retry_input(
                TYPE_INT,
                &guess,
                check_positive,
                "Please enter a number greater than 0, try again: "
            );
            if (guess == randomNumber) {
                printf("Congratulations, you guessed the number!\n");
                won = 1;

                break;
            }
        }

        if (!won) printf("Maximum amount of tries reached! The number was: %d\n", randomNumber);

        char repeat;

        printf("Do you want to try again?\n(Y/N):");
        retry_input(
            TYPE_CHAR,
            &repeat,
            check_yn,
            "Invalid output, try again:\n(Y/N):"
        );

        if (repeat == 'y' || repeat == 'Y') continue; else {
            printf("Got it! See you next time!\n");
            break;
        }
    }
    

    return 0;
}

void retry_input(InputType type, void *variable, int (*addCondition)(void *), char* errMessage) {
    while (1)
    {
        int succesful = 0;
        switch (type) {
            case TYPE_INT:
                succesful = scanf("%d", (int *)variable);
                break;
            case TYPE_CHAR:
                succesful = scanf(" %c", (char *)variable);
                break;
            case TYPE_STRING:
                succesful = scanf("%199s", (char *)variable);
                break;
        }

        if (succesful != 1) {
            printf("Invalid argument, non-matching value has been inputted, please try again...\n\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}

            continue;
        }

        if (addCondition(variable) == 1) { //I'm nesting here because I want to rather check if passed value is valid first before getting into the more type sensitive conditionals
            printf("%s\n\n", errMessage);
            continue;
        }

        break;
    }
    
}