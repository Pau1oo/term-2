#include "functions.h"

NODE* createNode(char* data)
{
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = strdup(data);
    node->yes = NULL;
    node->no = NULL;

    return node;
}

NODE* readTree(FILE *f)
{
    char data[MAX_QUESTION_LENGTH];
    if(fgets(data, sizeof(data), f) == NULL)
    {
        printf("Error");
        getch();
        fclose(f);
        return NULL;
    }
    if (data[0] == '@')
        return NULL;

    NODE* node = createNode(data);
    node->yes = readTree(f);
    node->no = readTree(f);

    return node;
}

void saveTree(NODE* node, FILE *f)
{
    if (node == NULL)
    {
        fprintf(f, "@\n");
        return;
    }

    fprintf(f, "%s", node->data);
    saveTree(node->yes, f);
    saveTree(node->no, f);
}

void freeTree(NODE* node)
{
    if (node != NULL)
    {
        if(node->yes != NULL)
            freeTree(node->yes);
        if(node->no != NULL)
            freeTree(node->no);
        free(node);
    }
}

NODE* guess_character(NODE** node)
{
    char answer[MAX_QUESTION_LENGTH];

    while ((*node)->yes != NULL || (*node)->no != NULL)
    {
        printf("%s? (yes/no)\n", (*node)->data);
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "yes") == 0)
            *node = (*node)->yes;
        else if (strcmp(answer, "no") == 0)
            *node = (*node)->no;
        else
            printf("Invalid input\n");
    }

    printf("%s? (yes/no)\n", (*node)->data);
    fgets(answer, MAX_NAME_LENGTH, stdin);
    answer[strcspn(answer, "\n")] = '\0';

    if (strcmp(answer, "yes") == 0)
    {
        printf("I win!\n");
        return *node;
    }
    else if (strcmp(answer, "no") == 0)
    {
        printf("I give up. Who is your person?\n");
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = '\0';

        printf("Provide a yes/no question that distinguishes %s from %s:\n", answer, (*node)->data);
        char question[MAX_QUESTION_LENGTH];
        fgets(question, MAX_QUESTION_LENGTH, stdin);
        question[strcspn(question, "\n")] = '\0';

        // Создаем два новых узла для ответов "yes" и "no"
        NODE* yesNode = createNode(answer);
        NODE* noNode = createNode((*node)->data);

        // Обновляем текущий узел
        strcpy((*node)->data, question);
        (*node)->yes = yesNode;
        (*node)->no = noNode;

    }
    else
        printf("Invalid input\n");

    return NULL;
}