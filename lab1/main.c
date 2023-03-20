#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main()
{
	int N; ram* rams = malloc(0);

    inputSize(&N);
    init(&rams, &N);

    while (1)
    {
        int choice;
        printf("\n");
        printf(" | [1] Print  | \n | [2] Add    | \n | [3] Delete | \n | [4] Sort   | \n | [0] Exit   | \n");
        printf("\n");
        while (!scanf("%d", &choice) || choice > 4 || choice < 0 || getchar() != '\n')
        {
            printf("Wrong input!\n");
            printf("Enter again: ");
            rewind(stdin);
        }

        if (choice == 0) 
            return 1;

        else if 
            (choice == 1) print(rams, &N);

        else if 
            (choice == 2) add(&rams, &N);

        else if 
            (choice == 3) delete(&rams, &N);

        else if 
            (choice == 4) sort(rams, N);

        printf("\n");
    }
}