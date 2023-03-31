#ifndef ANALOGOFAKINATOR_FUNCTIONS_H
#define ANALOGOFAKINATOR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 100
#define MAX_QUESTION_LENGTH 100

typedef struct Node {
    char data[MAX_NAME_LENGTH];
    struct Node* left;
    struct Node* right;
} NODE;

NODE* createNode(char* data);

void freeTree(NODE* root);

void saveTree(NODE* root, FILE* f);

NODE* guess_character(NODE* root);

#endif //ANALOGOFAKINATOR_FUNCTIONS_H
