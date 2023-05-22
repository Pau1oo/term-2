#ifndef LAB5_FUNCTIONS_H
#define LAB5_FUNCTIONS_H
#define CAPACITY 10
#define MAX_LENGTH 30
#define MAX_STRING_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct ITEM
{
    char* key;
    char* value;
    struct ITEM* prev;
    struct ITEM* next;
} ITEM;

typedef struct LRUCache
{
    int capacity;
    int count;
    ITEM* head;
    ITEM* tail;
    ITEM** items;
} LRUCache;

int menu();

ITEM* createItem(char* key, char* value);

LRUCache* createLRUCache(int capacity);

void getDomain(LRUCache* cache);

void printCache(LRUCache * cache);


#endif //LAB5_FUNCTIONS_H
