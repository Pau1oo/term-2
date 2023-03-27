#ifndef LAB2_FUNCTIONS_H
#define LAB2_FUNCTIONS_H
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct
{
    char* word;
    int freq;
    int flag;
    int length;
    struct FILO* next;
} FILO;

typedef struct
{
    char** words;
    int size;
} mas;

void push(FILO** head, char* word, int freq);

void createStack(FILO** head, mas* dividedText);

mas* splitText(char name[]);

void compression(char name[]);

int compare(FILO* head, char* word);

#endif //LAB2_FUNCTIONS_H
