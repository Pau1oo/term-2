#include "functions.h"

void saveTree(NODE* root, FILE* f)
{
    if (root == NULL)
        return;

    fprintf(f, "%s\n", root->data);
    saveTree(root->left, f);
    saveTree(root->right, f);
}

void freeTree(NODE* root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

NODE* createNode(char* data)
{
    NODE* node = malloc(sizeof(NODE));
    strcpy(node->data, data);
    node->left = NULL;
    node->right = NULL;

    return node;
}

NODE* guess_character(NODE* root)
{
    char answer[MAX_NAME_LENGTH];

    while (root->left != NULL || root->right != NULL)
    {
        printf("%s? (yes/no)\n", root->data);
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "yes") == 0)
            root = root->left;
        else if (strcmp(answer, "no") == 0)
            root = root->right;
        else
            printf("Invalid input\n");
    }

    printf("%s? (yes/no)\n", root->data);
    fgets(answer, MAX_NAME_LENGTH, stdin);
    answer[strcspn(answer, "\n")] = '\0';

    if (strcmp(answer, "yes") == 0)
    {
        printf("I win!\n");
        return root;
    }
    else if (strcmp(answer, "no") == 0)
    {
        printf("I give up. Who is your person?\n");
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = '\0';

        printf("Provide a yes/no question that distinguishes %s from %s:\n", answer, root->data);
        char question[MAX_QUESTION_LENGTH];
        fgets(question, MAX_QUESTION_LENGTH, stdin);
        question[strcspn(question, "\n")] = '\0';

        // Создаем два новых узла для ответов "yes" и "no"
        NODE* yesNode = createNode(answer);
        NODE* noNode = createNode(root->data);

        // Обновляем текущий узел
        strcpy(root->data, question);
        root->left = yesNode;
        root->right = noNode;

    }
    else
        printf("Invalid input\n");

    return NULL;
}
