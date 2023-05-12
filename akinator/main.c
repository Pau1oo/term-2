#include "functions.h"

int main()
{
    NODE* root = NULL;
    FILE* f = fopen("akinator.txt", "r");

    if(f == NULL)
    {
        exit(0);
    }

    root = readTree(f);
    fclose(f);

    guess_character(&root);
    f = fopen("akinator.txt", "w");

    if(f == NULL)
    {
        exit(0);
    }
    saveTree(root, f);
    fclose(f);
    freeTree(root);
    return 0;
}
