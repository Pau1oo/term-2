#ifndef AKINATOR_FUNCTIONS_H
#define AKINATOR_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_QUESTION_LENGTH 100
#define MAX_NAME_LENGTH 100

typedef struct NODE {
    char* data;
    struct NODE* yes;
    struct NODE* no;
} NODE;

NODE* createNode(char* data);

void freeTree(NODE* node);

NODE* readTree(FILE *f);

void saveTree(NODE* node, FILE* f);

NODE* guess_character(NODE** node);

#endif //AKINATOR_FUNCTIONS_H
