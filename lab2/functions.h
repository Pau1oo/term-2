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
} FILO;

FILO* createStack();

void push(FILO* stack, char* word);





#endif //LAB2_FUNCTIONS_H
