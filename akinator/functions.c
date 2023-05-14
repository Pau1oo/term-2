#include "functions.h"

NODE* newNode(char* data)
{
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->data = data;
    node->yesAnswer = NULL;
    node->noAnswer = NULL;

    return node;
}

NODE* readTree(FILE *f)
{
    char* data = malloc(sizeof(char) * MAX_QUESTION_LENGTH);
    if(!fgets(data, MAX_QUESTION_LENGTH, f))
    {
        return NULL;
    }

    data[strlen(data) - 1] = '\0';
    if (strcmp(data, "@") == 0)
        return NULL;

    NODE* node = newNode(data);
    node->noAnswer = readTree(f);
    node->yesAnswer = readTree(f);

    return node;
}

void saveTree(NODE* node, FILE *f)
{
    if (node == NULL)
    {
        fprintf(f, "@\n");
        return;
    }

    fprintf(f, "%s\n", node->data);
    saveTree(node->yesAnswer, f);
    saveTree(node->noAnswer, f);
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

NODE* guessCharacter(NODE* node)
{
    char *answer;
    printf("%s (yes/no)\n", node->data);

    if(node->noAnswer == NULL && node->yesAnswer == NULL)
    {
        fgets(answer, MAX_ANSWER_LENGTH, stdin);
        rewind(stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "yes") == 0)
        {
            printf("I win!");
            return NULL;
        }
        else
        {
            printf("I give up. Who is your person?\n");
            char* answerForQuestion = malloc(sizeof(char) * MAX_NAME_LENGTH);
            rewind(stdin);
            fgets(answerForQuestion, MAX_NAME_LENGTH, stdin);
            answerForQuestion[strcspn(answerForQuestion, "\n")] = '\0';

            printf("How can I differ this person?\n");
            char* mainString = malloc(sizeof(char) * MAX_QUESTION_LENGTH);
            rewind(stdin);
            fgets(mainString, MAX_QUESTION_LENGTH, stdin);
            rewind(stdin);
            mainString[strcspn(mainString, "\n")] = '\0';

            NODE* tempTreeNode = newNode(answerForQuestion);
            NODE* treeNodeNew = newNode(node->data);
            node->data = mainString;
            node->noAnswer = tempTreeNode;
            node->yesAnswer = treeNodeNew;
            return NULL;
        }
    }
    else
    {
        fgets(answer, MAX_ANSWER_LENGTH, stdin);
        rewind(stdin);
        answer[strcspn(answer, "\n")] = '\0';

        if (strcmp(answer, "yes") == 0)
        {
            return node->noAnswer;
        }
        else
        {
            return node->yesAnswer;
        }
    }
}

void game(NODE* root)
{
    while (1)
    {
        NODE* tempRoot = root;
        do
        {
            tempRoot = guessCharacter(tempRoot);
        } while (tempRoot != NULL);

        FILE* f = fopen("akinator.txt", "w");
        if (f == NULL)
        {
            exit(0);
        }
        saveTree(root, f);
        fclose(f);
        break;
    }
}