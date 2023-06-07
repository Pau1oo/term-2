#ifndef LAB5_FUNCTIONS_H
#define LAB5_FUNCTIONS_H
#define ERROR_OPENING 5
#define CAPACITY 5
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
    struct ITEM* nextCollision;
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

void getIP(LRUCache* cache);

void printCache(LRUCache * cache);

void addDomainAndIPToTheFile();

int validateDuplication(char* key);

void recordingTypeCNAME(FILE* file);

void recordingTypeA(FILE* file);

int validateIP(const char *ip);

void getDomain(LRUCache* cache);

#endif //LAB5_FUNCTIONS_H
