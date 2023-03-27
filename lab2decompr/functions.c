#include "functions.h"

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

void swap(mas* text, char* first, char* second)
{
    for (int i = 0; i < text->size; ++i)
    {
        if(strcmp(text->words[i], first) == 0)
            text->words[i] = second;
        else
        if(strcmp(text->words[i], second) == 0)
            text->words[i] = first;
    }
}

mas* splitIntoWords(char* text)
{
    mas* array = malloc(sizeof(mas));
    array->size = 0;
    array->words = NULL;

    char* word = strtok(text, " ");

    while(word != NULL)
    {
        array->words = realloc(array->words, (array->size + 1) * sizeof(char*));
        array->words[array->size++] = word;
        word = strtok(NULL, " ");
    }
    return array;
}

mas* splitIntoString(char name[])
{
    FILE* f = fopen(name, "r");
    if(f == NULL)
    {
        printf("File not found.\n");
        return 0;
    }

    mas* array = malloc(sizeof(mas));
    array->size = 0;
    array->words = NULL;

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* text = calloc(length, 1);

    fread(text, 1, length, f);
    fclose(f);

    char* string = strtok(text, "\n");

    while(string != NULL)
    {
        array->words = realloc(array->words, (array->size + 1) * sizeof(char*));
        array->words[array->size++] = string;

        string = strtok(NULL, "\n");
    }
    return array;
}

void decompression()
{
    mas* compressedText = splitText("compressed.txt");
    if(compressedText == NULL)
        exit(0);

    FILE* f = fopen("compressed.txt", "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    printf("Compressed size: %ld\n", size);

    mas* compressedTools = splitIntoString("replacement.txt");
    if(compressedTools == NULL)
        exit(0);

    f = fopen("replacement.txt", "rb");
    fseek(f, 0, SEEK_END);
    long tools_size = ftell(f);
    printf("Tools size: %ld\n", tools_size);
    printf("Full size: %ld\n\n", size + tools_size);

    printf("Processing...\n\n");

    for (int i = 0; i < compressedTools->size; ++i)
    {
        mas* word = splitIntoWords(compressedTools->words[i]);
        if(word->size != 2)
            continue;
        swap(compressedText, word->words[0], word->words[1]);
    }

    fclose(fopen("decompressed.txt", "w"));

    f = fopen("decompressed.txt", "ab");
    if(f == NULL)
        exit(0);

    for (int i = 0; i < compressedText->size; ++i)
    {
        fputs(compressedText->words[i], f);
        if(i != compressedText->size - 1)
            fputs(" ", f);
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fclose(f);

    printf("Decompressed size: %ld\n", size);
    printf("File decompressed!!!\n");
}