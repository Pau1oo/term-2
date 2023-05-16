#include "functions.h"

int main()
{
    FILE* f = fopen("akinator.txt", "r");
    if(f == NULL)
    {
        exit(0);
    }

    NODE* root = readTree(f);
    fclose(f);
    game(root);
    freeTree(root);
    return 0;
}
