#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

enum ERRORS
{
    SIZE_IS_NULL  = 1,
    LIST_OVERFLOW = -1,
    NO_ERRORS
};

static const int START_OF_LABLE  = 0;
static const int END_OF_LABLE    = 0;
static const int START_HEAD      = 1;
static const int START_TAIL      = 0;

typedef int List_t;

typedef struct List
{
    List_t* data;
    List_t* next;
    List_t* prev;

    int capacity;
    int size;
    int head;
    int tail;
} LIST;


int ListCtor(LIST* lst, int size);
int ListVerify(LIST* lst);
int FindFreeSell(List_t* arr, int capacity);
int ListDtor(LIST* lst);

int ListDump(LIST* lst);
int MakeDotFile(LIST* lst, FILE* Dump);
int PrintArray(List_t* Arr, int capacity, FILE* file);

#endif
