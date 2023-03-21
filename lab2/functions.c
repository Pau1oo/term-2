#include "functions.h"

FILO* createStack()
{
    FILO* stack = malloc(sizeof(FILO));
    stack->head = -1;
    return stack;
}

void push(FILO* stack, char* word)
{
    stack->word[++stack->head] = malloc(strlen(word) + 1);
    strcpy(stack->word[stack->head], word);
}

char* pop(FILO* stack)
{
    char* word = stack->word[stack->head];
    stack->word[stack->head] = NULL;
    stack->head--;
    return word;
}

void splitText(FILO* stack)
{
    FILE* f = fopen("text.txt", "r");
    if(f == NULL)
    {
        printf("Error opening file...\n");
        exit(1);
    }

    while(!feof(f))
    {
        char* str = strtok()
    }
}