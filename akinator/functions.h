#ifndef AKINATOR_FUNCTIONS_H
#define AKINATOR_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <mmsystem.h>
#define MAX_QUESTION_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_ANSWER_LENGTH 4

typedef struct NODE
{
    char* data;
    struct NODE* yesAnswer;
    struct NODE* noAnswer;
} NODE;

NODE* newNode(char* data);

void freeTree(NODE* node);

NODE* readTree(FILE *f);

void saveTree(NODE* node, FILE* f);

void guessCharacter(NODE* node);

void game(NODE* root);

#endif //AKINATOR_FUNCTIONS_H
