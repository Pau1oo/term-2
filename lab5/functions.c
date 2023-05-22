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

void getDomain(LRUCache* cache)
{
    printf("Input a domain:\n");
    char* key = getStringFromStdin();
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




