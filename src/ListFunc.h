#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"../MyStack/StackFunc.h"

enum ERRORS
{
    SIZE_IS_NULL  = 1,
    LIST_OVERFLOW = -1,
    NO_ERROR
};

// static const int START_OF_LABLE  = 0;
// static const int END_OF_LABLE    = 0;
static const int START_HEAD      = 1;
static const int START_TAIL      = 0;

typedef int List_t;

typedef struct List
{
    List_t* data;
    List_t* next;
    List_t* prev;

    Stack_t free_stk;

    int capacity;
    int size;
    //int head;
    //int tail;
} LIST;


int ListCtor(LIST* lst, size_t size);
int ListVerify(LIST* lst);
int ListPush(LIST* lst, List_t element, int index);
//int ListAppend(LIST* lst, List_t element);
//int GetFirstPTR(LIST* lst);
//int FindFreeSell(List_t* arr, int capacity);
int ListDtor(LIST* lst);

int ListDump(LIST* lst);
int MakeDotFile(LIST* lst, FILE* Dump);
int PrintArray(List_t* Arr, int capacity, FILE* file);

#endif
