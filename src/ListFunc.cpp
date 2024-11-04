#include"ListFunc.h"

static const int Poison_lable = 0;

int ListCtor(LIST* lst, size_t size)
{
    assert(lst);

    lst->data     = (List_t*)calloc(size, sizeof(List_t)); assert(lst->data);
    lst->next     = (List_t*)calloc(size, sizeof(List_t)); assert(lst->next);
    lst->prev     = (List_t*)calloc(size, sizeof(List_t)); assert(lst->prev);

    lst->capacity = size;
    StackCtor(&lst->free_stk, lst->capacity);
    // lst->data[0]        = START_OF_LABLE;
    // lst->data[1]        = END_OF_LABLE;
    ListVerify(lst);
    lst->size     = 2;
    //lst->head     = START_HEAD;
    //lst->tail     = START_TAIL;

    return NO_ERRORS;
}


int ListVerify(LIST* lst)
{
    assert(lst);

    // if(lst->size == 0)
    // {
    //     return SIZE_IS_NULL;
    // }

    for(int i = START_HEAD; i < lst->capacity; i++)
    {
        lst->data[i] = Poison_lable;
        lst->next[i] = i + 1;
        lst->prev[i] = i - 1;

        size_t free = lst->capacity - i;
        StackPush(&lst->free_stk, (double)free);
    }

    lst->next[0] = lst->capacity - 1;
    lst->prev[0] = lst->capacity - 1;

    lst->next[lst->capacity - 1] = 0;
    lst->prev[lst->capacity - 1] = 0;

    return NO_ERRORS;
}

// int GetFirstPTR(LIST* lst)
// {
//     assert(lst);
//     int i = 0;
//     while(lst->prev[i] == 0)
//         ++i;
//
//     return lst->prev[i];
// }


int ListPush(LIST* lst, List_t element, int index) // add an element after input index
{                                                  // if it is the fers element, index must be 0
    assert(lst);

    double sell = 0;
    if(StackPop(&lst->free_stk, &sell) == STACK_UNDERFLOW)
    {
        return LIST_OVERFLOW;
    }
    //fprintf(stderr, "sell = %d\n", (int)sell);

    lst->data[lst->size - 1] = element;
    ++lst->size;

    lst->next[(int)sell] = lst->next[index];
    lst->prev[(int)sell] = index;

    lst->next[index]     = (int)sell;
    lst->prev[(int)sell + 1] = (int)sell;

    return NO_ERRORS;
}


int ListDtor(LIST* lst)
{
    assert(lst);

    StackDtor(&lst->free_stk);
    free(lst->data);
    free(lst->next);
    free(lst->prev);

    return NO_ERRORS;
}

// int ListAppend(LIST* lst, List_t element)
// {
//     assert(lst);
//
//     if (lst->head >= lst->size)
//     {
//         fprintf(stderr, "List overflow! Element %d will not be written!\n", element);
//         return LIST_OVERFLOW;
//     }
//
//     if ((lst->head == START_HEAD) && (lst->size == 0))
//     {
//         lst->data[START_HEAD] = element;
//         lst->prev[START_HEAD] = 0;
//         ++lst->size;
//         ++lst->head;
//         return NO_ERRORS;
//     }
//
//     lst->data[lst->size]     = element;
//     lst->next[lst->head - 1] = lst->head;
//     lst->next[lst->head + 1] = 0;
//     lst->prev[lst->head]     = lst->head - 1;
//
//     ++lst->head;
//     ++lst->tail;
//
//     return NO_ERRORS;
// }


// int FindFreeSell(List_t* arr, int capacity)
// {
//     assert(arr);
//
//     for(int i = START_HEAD + 1; i < capacity; i++)
//     {
//         if( arr[i] == Poison_lable)
//         {
//             return i;
//         }
//     }
//
//     return LIST_OVERFLOW;
// }



