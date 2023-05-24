#include "functions.h"

int main()
{
    LRUCache* cache = createLRUCache(CAPACITY);

    while(1)
    {
        int choice = menu();

        if (choice == 0) exit(0);

        else if
                (choice == 1) printCache(cache);

        else if
                (choice == 2)
            getIP(cache);

        else if
                (choice == 3) addDomainAndIPToTheFile();

        else if
                (choice == 4) getDomain();

        printf("\n");
    }
}
