#include "functions.h"

FILO* getLast(FILO* head)
{
    if(head == NULL)
        return NULL;

    while(head->next)
        head = head->next;

    return head;
}

void push(FILO** head, char* word, int freq)
{
    FILO* tail = getLast(*head);
    FILO* stack = (FILO*)malloc(sizeof(FILO));

    stack->word = word;
    stack->freq = freq;
    stack->flag = 0;
    stack->length = (int)strlen(word);
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

void divideFILO(FILO* head, FILO** first, FILO** last)
{
    FILO* temp1 = NULL;
    FILO* temp2 = NULL;

    if(head == NULL || head->next == NULL)
    {
        (*first) = head;
        (*last)  = NULL;
        return;
    }

    temp2 = head;
    temp1 = head->next;

    while (temp1 != NULL)
    {
        temp1 = temp1->next;

        if(temp1 != NULL)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    (*first) = head;
    (*last) = temp2->next;
    temp2->next = NULL;
}

void merging(FILO *a, FILO *b, FILO **c)
{
    FILO temp;
    *c = NULL;

    if (a == NULL)
    {
        *c = b;
        return;
    }

    if (b == NULL)
    {
        *c = a;
        return;
    }

    if (a->freq * a->length > b->freq * b->length)
    {
        *c = a;
        a = a->next;
    }
    else
    {
        *c = b;
        b = b->next;
    }

    temp.next = *c;

    while (a && b)
    {
        if (a->freq * a->length > b->freq * b->length)
        {
            (*c)->next = a;
            a = a->next;
        }
        else
        {
            (*c)->next = b;
            b = b->next;
        }
        (*c) = (*c)->next;
    }

    if (a)
    {
        while (a)
        {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    }

    if (b)
    {
        while (b)
        {
            (*c)->next = b;
            (*c) = (*c)->next;
            b = b->next;
        }
    }
    *c = temp.next;
}

void mergeSort(FILO** head)
{
    FILO* first = NULL;
    FILO* last = NULL;

    if((*head == NULL) || ((*head)->next == NULL))
        return;

    divideFILO(*head, &first, &last);
    mergeSort(&first);
    mergeSort(&last);
    merging(first, last, head);
}

void createStack(FILO** head, mas* dividedText)
{
    for (int i = 0; i < dividedText->size; i++)
    {

        if (compare(*head, dividedText->words[i]))
            continue;
        if (strstr(dividedText->words[i], "\n") != NULL)
            continue;

        int freq = 0;
        for (int j = 0; j < dividedText->size; j++)
            if (strcmp(dividedText->words[i], dividedText->words[j]) == 0)
                freq++;
        push(&(*head), dividedText->words[i], freq);
    }
    mergeSort(&(*head));
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

void setFlag(FILO* head, char* word)
{
    while(head)
    {
        if(strcmp(head->word, word) == 0)
        {
            head->flag = 1;
            return;
        }
        head = head->next;
    }
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

int profit(FILO* first, FILO* second)
{
    if(first->freq <= second->freq)
        return 0;
    else if(first->flag || second->flag)
            return -1;
    else
        return (first->freq*first->length + second->freq*second->length) -
                (first->freq*second->length + second->freq*first->length) -
                (first->length + second->length + 2);
}

void replaceWords(FILO* head, mas* dividedText)
{
    FILO* first = head;

    fclose(fopen("replacement.txt", "w"));

    while(first)
    {
        int max = 0;
        char* word;
        FILO* second = head;

        while(second)
        {
            int catch = profit(first, second);
            if(catch > max)
            {
                max = catch;
                word = second->word;
            }

            second = second->next;

        }

        if(max > 0)
        {
            setFlag(head, first->word);
            setFlag(head, word);

            if(strlen(word) == 0 || strlen(first->word) == 0)
                continue;

            swap(dividedText, first->word, word);

            FILE* f = fopen("replacement.txt", "ab");
            if(f == NULL)
                exit(0);

            fputs(first->word, f);
            fputs(" ", f);
            fputs(word, f);
            fputs("\n", f);
            fclose(f);
        }

        first = first->next;
    }
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

    FILO* head = NULL;

    createStack(&head, dividedText);
    replaceWords(head, dividedText);

   // fclose(fopen("compressed.txt", "w"));

    fclose(f);
    f = fopen("compressed.txt", "ab");
    if(f == NULL)
        exit(0);

    for (int i = 0; i < dividedText->size; ++i)
    {
        fputs(dividedText->words[i], f);
        if(i != dividedText->size - 1)
            fputs(" ", f);
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    printf("Compressed size: %ld\n", size);

    fclose(f);
    f = fopen("replacement.txt", "rb");
    fseek(f, 0, SEEK_END);
    long replacement_size = ftell(f);
    fclose(f);

    printf("Replacement word size: %ld\n", replacement_size);
    printf("Compressed size + replacement tools size: %ld\n", size + replacement_size);
    printf("File compressed!!!\n");

    for (int i = dividedText->size; dividedText->words[i]!=NULL; --i)
    {
        free(dividedText->words[i]);
    }

    free(dividedText->words);
    free(dividedText);
}