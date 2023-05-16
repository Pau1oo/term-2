#include "functions.h"

void saveTree(NODE *node, FILE *f)
{
    if (node == NULL)
    {
        fprintf(f, "@\n");
        return;
    }

    fprintf(f, "%s", node->data);
    saveTree(node->yesAnswer, f);
    saveTree(node->noAnswer, f);
}

NODE* readTree(FILE* f)
{
    char data[100];
    fgets(data, sizeof(data), f);
    if (data[0] == '@')
        return NULL;

    NODE *node = newNode(data);
    node->yesAnswer = readTree(f);
    node->noAnswer = readTree(f);

    return node;
}

NODE* newNode(char* data)
{
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = strdup(data);
    node->yesAnswer = NULL;
    node->noAnswer = NULL;

    return node;
}

void freeTree(NODE* node)
{
    if (node != NULL)
    {
        if(node->yesAnswer != NULL)
            freeTree(node->yesAnswer);
        if(node->noAnswer != NULL)
            freeTree(node->noAnswer);
        free(node);
    }
}

char* getStringFromStdin()
{
    int length = 1;
    char* string = (char *) malloc(length * sizeof(char));
    for (int i = 0;; i++)
    {
        string[i] = (char) getchar();
        if (string[i] == '\n')
        {
            string[i] = '\0';
            break;
        }
        length++;
        string = (char *) realloc(string, length);
    }
    return string;
}

void guessCharacter(NODE *node)
{
    printf("%s\n", node->data);

    char* answer = getStringFromStdin();
    while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0)
    {
        printf("Input \"yes\" or \"no\"\n");
        rewind(stdin);
        answer = getStringFromStdin();
    }
    system("cls");

    if (strcmp(answer, "yes") == 0)
    {
        if (node->yesAnswer == NULL)
        {
            printf("I win!\n");
            free(answer);
            getch();
        }
        else
        {
            free(answer);
            guessCharacter(node->yesAnswer);
        }
    }
    else
    {
        free(answer);
        if (node->noAnswer == NULL)
        {
            printf("I give up. Who is your person?\n");
            char* newPerson = getStringFromStdin();

            printf("Write a question that differ %s from %s?\n", newPerson, node->data);
            char* questionForNewPerson = getStringFromStdin();
            questionForNewPerson = realloc(questionForNewPerson, strlen(questionForNewPerson) + 1);
            strcat(questionForNewPerson, "\n");

            NODE* new_node = newNode(questionForNewPerson);
            free(questionForNewPerson);

            newPerson = realloc(newPerson, strlen(newPerson) + 1);
            strcat(newPerson, "\n");

            new_node->yesAnswer = newNode(newPerson);
            new_node->noAnswer = newNode(node->data);
            free(newPerson);
            memcpy(node, new_node, sizeof(NODE));
            free(new_node);
        }
        else
            guessCharacter(node->noAnswer);
    }
}

void game(NODE* root)
{
    guessCharacter(root);
    FILE* f = fopen("akinator.txt", "w");
    if (f == NULL)
    {
        exit(0);
    }
    saveTree(root, f);
    fclose(f);
}




