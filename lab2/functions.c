#include "functions.h"

FILO* createStack()
{
    FILO* stack = malloc(sizeof(FILO));
    stack->head = 0;
    return stack;
}