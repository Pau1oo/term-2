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

mas* splitText(char name[])
{
    FILE* f = fopen(name, "r");

    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(f == NULL)
    {
        printf("Error opening file...\n");
        return 0;
    }

    mas* array = malloc(sizeof(mas));
    array->size = 0;
    array->words = NULL;

    char* text = malloc(len);
    fread(text, 1, len, f);
    fclose(f);

    char* word = strtok(text, " ");
    while(word != NULL)
    {
        array->words = realloc(array->words, (array->size + 1) * sizeof(char*));
        array->words[array->size++] = word;
        word = strtok(NULL, " ");
    }
}