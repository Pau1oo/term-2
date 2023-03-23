#ifndef LAB2_FUNCTIONS_H
#define LAB2_FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct
{
    char* word;
    int head;
    struct FILO* next;
} FILO;

typedef struct
{
    char** words;
    int size;
} mas;

FILO* createStack();

void push(FILO* stack, char* word);

mas* splitText(char name[]);


#endif //LAB2_FUNCTIONS_H
