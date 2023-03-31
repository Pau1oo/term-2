#include "functions.h"

int main()
{
    NODE* root = NULL;
    FILE* f = fopen("akinator.txt", "r");

    if (f == NULL)
        root = createNode("Plotva");
    else
    {
        char line[MAX_NAME_LENGTH];
        fgets(line, MAX_NAME_LENGTH, f);
        line[strcspn(line, "\n")] = '\0';

        root = createNode(line);
        NODE* currentNode = root;

        while (fgets(line, MAX_NAME_LENGTH, f))
        {
            line[strcspn(line, "\n")] = '\0';

            if (currentNode->left == NULL)
                currentNode->left = createNode(line);
            else if (currentNode->right == NULL)
                currentNode->right = createNode(line);
            else
            {
                while (currentNode->left != NULL && currentNode->right != NULL)
                    currentNode = currentNode->left;

                if (currentNode->left == NULL)
                    currentNode->left = createNode(line);
                else
                    currentNode->right = createNode(line);
            }
        }
        fclose(f);
    }

    while (1)
    {
        char answer[MAX_NAME_LENGTH];
        printf("Think of a character, and I will try to guess it. Ready? (yes/no)\n");
        fgets(answer, MAX_NAME_LENGTH, stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "no") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(answer, "yes") == 0)
        {
            NODE* result = guess_character(root);

            if (result != NULL)
            {
                f = fopen("akinator.txt", "w");
                saveTree(root, f);
                fclose(f);

                freeTree(root);
                break;
            }
        }
        else
            printf("Invalid input\n");
    }
    return 0;
}