#include "functions.h"

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
        string = (char *) realloc(string, length * sizeof(char));
    }
    return string;
}

void displayMenu()
{
    printf("[1] Print cache\n");
    printf("[2] Search for an IP by a domain\n");
    printf("[3] Add domain and IP address to the file\n");
    printf("[4] Search for a domain by IP address\n");
    printf("[0] Exit\n");
}

int menu()
{
    int choice;
    system("cls");
    displayMenu();
    while (!scanf_s("%d", &choice) || choice > 4 || choice < 0 || getchar() != '\n')
    {
        system("cls");
        printf("Invalid choice!\n");
        printf("Choose again!\n");
        printf("\n");
        displayMenu();
        rewind(stdin);
    }
    system("cls");
    return choice;
}

unsigned long hash(const char* domain)
{
    unsigned long i = 0;
    for (int j = 0; domain[j]; j++)
        i += domain[j];

    return i % CAPACITY;
}

ITEM* createItem(char* key, char* value)
{
    ITEM* newItem = (ITEM*)malloc(sizeof(ITEM));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->prev = NULL;
    newItem->next = NULL;
    return newItem;
}

LRUCache* createLRUCache(int capacity)
{
    LRUCache* cache = (LRUCache*) malloc(sizeof(LRUCache));

    if (cache == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    cache->capacity = capacity;
    cache->count = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->items = (ITEM**) calloc(cache->capacity, sizeof(ITEM*));
    for (int i = 0; i < capacity; i++)
        cache->items[i] = NULL;

    return cache;
}

void removeNode(LRUCache* cache, ITEM* item)
{
    if (item->prev != NULL)
        item->prev->next = item->next;
    else
        cache->head = item->next;

    if (item->next != NULL)
        item->next->prev = item->prev;
    else
        cache->tail = item->prev;
}

void addToFront(LRUCache* cache, ITEM* item)
{
    item->next = cache->head;
    item->prev = NULL;
    if (cache->head != NULL)
        cache->head->prev = item;
    cache->head = item;

    if (cache->tail == NULL)
        cache->tail = item;
}

void updateLRUCache(LRUCache* cache, ITEM* item)
{
    removeNode(cache, item);
    addToFront(cache, item);
}

char* findKeyFromFile(char* key)
{
    FILE* file = fopen("DNS.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    char string[MAX_STRING_SIZE];
    char* keyDomain = malloc(MAX_LENGTH * sizeof(char));
    char* tempDomain = malloc(MAX_LENGTH * sizeof(char));
    char* value = malloc(MAX_LENGTH * sizeof(char));
    char* result = NULL;
    char* type = malloc(MAX_LENGTH * sizeof(char));

    while (fgets(string, sizeof(string), file) != NULL)
    {
        if(sscanf(string, "%255s IN %255s %255s", keyDomain, type, value) == 3 && strcmp(keyDomain, key) == 0)
        {
            strcpy(tempDomain, key);
            if(strcmp(type, "A") == 0)
            {
                result = strdup(value);
                break;
            }
            else if(strcmp(type, "CNAME") == 0)
            {
                rewind(file);
                strcpy(key, value);
                while(fgets(string, sizeof(string), file) != NULL)
                {
                    if(sscanf(string, "%255s IN %255s %255s", keyDomain, type, value) == 3 && strcmp(keyDomain, key) == 0)
                    {
                        strcpy(key, tempDomain);
                        result = strdup(value);
                        break;
                    }
                }
            }
        }
    }

    fclose(file);
    free(keyDomain);
    free(tempDomain);
    free(value);
    free(type);

    if (result == NULL)
    {
        printf("Domain '%s' doesn't exist in cache nor file.\n", key);
        getch();
    }
    return result;
}

void put(LRUCache* cache, char* key, char* value)
{
    unsigned long index = hash(key);
    ITEM* item = cache->items[index];
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
        {
            free(item->value);
            item->value = strdup(value);
            updateLRUCache(cache, item);
            return;
        }
        item = item->next;
    }
    item = createItem(key, value);
    addToFront(cache, item);
    cache->items[index] = item;
    cache->count++;
    if (cache->count > cache->capacity)
    {
        ITEM* tail = cache->tail;
        cache->items[hash(tail->key)] = NULL;
        removeNode(cache, tail);
        free(tail->key);
        free(tail->value);
        free(tail);
        cache->count--;
    }
}

void get(LRUCache* cache, char* key)
{
    unsigned long index = hash(key);
    ITEM* item = cache->items[index];
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
        {
            updateLRUCache(cache, item);
            printf("%s - %s\n", key, item->value);
            getch();
            return;
        }
        item = item->next;
    }

    char* value = findKeyFromFile(key);
    if (value != NULL)
    {
        put(cache, key, value);
        printf("%s - %s\n", key, value);
        getch();
        free(value);
    }
}

void getIP(LRUCache* cache)
{
    printf("Input a domain:\n");
    char* key = getStringFromStdin();
    system("cls");
    if (key != NULL)
    {
        get(cache, key);
        free(key);
    }
}

void printCache(LRUCache* cache)
{
   ITEM* current = cache->head;
   while(current!=NULL)
   {
       printf("%s - %s\n", current->key, current->value);
       current = current->next;
   }
    getch();
}

int validateIP(const char *ip)
{
    int numFields = 0;
    int fieldValue = 0;
    int numDigits = 0;

    while (*ip)
    {
        if (*ip == '.')
        {
            if (numDigits == 0 || fieldValue > 255)
                return 0;
            numFields++;
            fieldValue = 0;
            numDigits = 0;
        }
        else if (*ip >= '0' && *ip <= '9')
        {
            fieldValue = fieldValue * 10 + (*ip - '0');
            numDigits++;
        }
        else
            return 0;

        ip++;
    }

    if (numDigits == 0 || fieldValue > 255)
        return 0;

    return (numFields == 3) ? 1 : 0;
}

int validateDuplication(char* key)
{
    FILE* file = fopen("DNS.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return ERROR_OPENING;
    }

    char string[MAX_STRING_SIZE];
    char* keyDomain = malloc(MAX_LENGTH * sizeof(char));
    char* value = malloc(MAX_LENGTH * sizeof(char));
    char* type = malloc(MAX_LENGTH * sizeof(char));

    while (fgets(string, sizeof(string), file) != NULL)
    {
        if(sscanf(string, "%255s IN %255s %255s", keyDomain, type, value) == 3 && strcmp(keyDomain, key) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void addDomainAndIPToTheFile()
{
    FILE* file = fopen("DNS.txt", "a");
    if(file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("What type of record to file do you want?\n[1] IN A\n[2] IN CNAME\n");
    int typeOfRecord;
    while(scanf_s("%d", &typeOfRecord) != 1 || typeOfRecord > 2 || typeOfRecord < 1 || getchar() != '\n')
    {
        system("cls");
        printf("Invalid input!\nTry again:\n");
    }

    if (typeOfRecord == 1)
    {
        system("cls");
        recordingTypeA(file);
    }
    else if (typeOfRecord == 2)
    {
        system("cls");
        recordingTypeCNAME(file);
    }
}

void recordingTypeCNAME(FILE* file)
{
    printf("Enter the domain you want to add to the file:\n");
    char* domain = getStringFromStdin();
    system("cls");

    while(validateDuplication(domain) == 1)
    {
        printf("Duplication detected!\nTry again:\n");
        free(domain);
        domain = getStringFromStdin();
        system("cls");
    }

    printf("Enter the second domain:\n");
    char* secondDomain = getStringFromStdin();
    system("cls");

    printf("Enter the IP address of domain '%s':\n", secondDomain);
    char* ip = getStringFromStdin();
    system("cls");
    while(validateIP(ip) == 0)
    {
        free(ip);
        printf("Invalid input!\nTry again:\n");
        ip = getStringFromStdin();
        system("cls");
    }

    if (validateDuplication(secondDomain) == 1)
    {
        fprintf(file, "%s IN CNAME %s\n", domain, secondDomain);
        fclose(file);
        return;
    }

    fprintf(file, "%s IN CNAME %s\n", domain, secondDomain);
    fprintf(file, "%s IN A %s\n", secondDomain, ip);
    fclose(file);
}

void recordingTypeA(FILE* file)
{
    printf("Enter the domain you want to add to the file:\n");
    char* domain = getStringFromStdin();
    system("cls");

    while(validateDuplication(domain) == 1)
    {
        printf("Duplication detected!\nTry again:\n");
        free(domain);
        domain = getStringFromStdin();
        system("cls");
    }

    printf("Enter the IP address of this domain:\n");
    char* ip = getStringFromStdin();
    system("cls");
    while(validateIP(ip) == 0)
    {
        free(ip);
        printf("Invalid input!\nTry again:\n");
        ip = getStringFromStdin();
        system("cls");
    }

    fprintf(file, "%s IN A %s\n", domain, ip);
    fclose(file);
}

void getDomain()
{
    FILE* file = fopen("DNS.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char string[MAX_STRING_SIZE];
    char* keyDomain = malloc(MAX_LENGTH * sizeof(char));
    char* tempDomain = malloc(MAX_LENGTH * sizeof(char));
    char* value = malloc(MAX_LENGTH * sizeof(char));
    char* type = malloc(MAX_LENGTH * sizeof(char));

    printf("Enter the IP address:\n");
    char* ip = getStringFromStdin();
    system("cls");
    while(validateIP(ip) == 0)
    {
        free(ip);
        printf("Invalid input!\nTry again:\n");
        ip = getStringFromStdin();
        system("cls");
    }

    while(fgets(string, sizeof(string), file) != NULL)
    {
        if(sscanf(string, "%255s IN A %255s", keyDomain, value) == 2 && strcmp(value, ip) == 0)
        {
            strcpy(tempDomain, keyDomain);
            rewind(file);
            while(fgets(string, sizeof(string), file) != NULL)
            {
                if(sscanf(string, "%255s IN CNAME %255s", keyDomain, value) == 2 && strcmp(tempDomain, value) == 0)
                {
                    printf("%s - %s\n", keyDomain, ip);
                    printf("%s - %s\n", tempDomain, ip);
                    getch();
                }
            }
        }
    }
}