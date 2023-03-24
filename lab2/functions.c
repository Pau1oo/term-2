#include "functions.h"

FILO* last(FILO* head)
{
    if(head == NULL)
        return NULL;

    while(head->next)
        head = head->next;

    return head;
}

void push(FILO** head, char* word, int freq)
{
    FILO* tail = last(*head);
    FILO* stack = (FILO*)malloc(sizeof(FILO));

    stack->word = word;
    stack->freq = freq;
    stack->next = NULL;

    if(*head == NULL)
    {
        *head = stack;
        return;
    }

    tail->next = stack;
}

mas* splitText(char name[])
{
    FILE* f = fopen(name, "r");

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
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
    return array;
}

void createStack(FILO** head, mas* divided_text)
{
    for (int i = 0; i < divided_text->size; i++)
    {

        if (compare(*head, divided_text->words[i])) continue;
        if (strstr(divided_text->words[i], "\n") != NULL) continue;

        int freq = 0;
        for (int j = 0; j < divided_text->size; j++)
            if (strcmp(divided_text->words[i], divided_text->words[j]) == 0)
                freq++;
        push(&(*head), divided_text->words[i], freq);
    }
}

int compare(FILO* head, char* word)
{
    while(head)
    {
        if(strcmp(head->word, word) == 0)
            return 1;

        head = head->next;
    }
    return 0;
}

void compression(char name[])
{
    mas* dividedText = splitText(name);

    if(dividedText == NULL)
    {
        printf("Splitting error!");
        exit(1);
    }

    FILE* f = fopen(name, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    printf("Initial size: %ld\n", size);
    printf("Splitting...\n");
}