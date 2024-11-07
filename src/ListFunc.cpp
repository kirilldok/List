#include"ListFunc.h"

static const int Poison_label = -666;

int ListCtor(LIST* lst, size_t size)
{
    assert(lst);

    lst->data     = (List_arg_t*)calloc(size, sizeof(List_arg_t)); assert(lst->data);
    lst->next     = (size_t*)calloc(size, sizeof(size_t)); assert(lst->next);
    lst->prev     = (size_t*)calloc(size, sizeof(size_t)); assert(lst->prev);

    lst->capacity = size;
    StackCtor(&lst->free_stk, lst->capacity);

    for(size_t i = 0; i < lst->capacity; i++)
    {
        lst->data[i] = Poison_label;
        lst->next[i] = i + 1;
        lst->prev[i] = FREE_label;

        size_t free = lst->capacity - i;
        StackPush(&lst->free_stk, (double)free);
    }

    lst->next[0] = 0; //initialising null element
    lst->prev[0] = 0;

    lst->data[0] = VAL_EMPTY;

    lst->size = 1;

    return NO_ERROR;
}


int ListVerify(LIST* lst)
{
    assert(lst);

    if(lst->size == 0)
    {
        return SIZE_IS_NULL;
    }

    if(lst->capacity == 0)
    {
        return LIST_OVERFLOW;
    }

    if(lst->data == NULL)
    {
        return DATA_IS_NULL;
    }

    if(lst->next == NULL)
    {
        return NEXT_IS_NULL;
    }

    if(lst->prev== NULL)
    {
        return PREV_IS_NULL;
    }

    if(lst->data[0] != VAL_EMPTY)
    {
        return NULL_PTR_DATA_CORRUPTED;
    }

    return NO_ERROR;
}


int ListPushInd(LIST* lst, List_arg_t element, size_t index) // add an element after input index
{                                                  // if it is the fers element, index must be 0
    assert(lst);

    double sell = 0;
    if(StackPop(&lst->free_stk, &sell) == STACK_UNDERFLOW)
    {
        return LIST_OVERFLOW;
    }
    //fprintf(stderr, "sell = %lu\n", (size_t)sell);
    //++lst->size;
    lst->data[lst->size] = element;
    ++lst->size;

    lst->next[(size_t)sell] = lst->next[index];
    lst->prev[(size_t)sell] = index;

    lst->prev[lst->next[index]] = (size_t)sell;
    lst->next[index]            = (size_t)sell;

    return NO_ERROR;
}


int ListPopInd(LIST* lst, size_t index)
{
    assert(lst);

    StackPush(&lst->free_stk, (double)index);
    lst->data[index] = Poison_label;

    lst->next[lst->prev[index]] = lst->next[index];
    lst->prev[lst->next[index]] = lst->prev[index];

    lst->next[index] = lst->prev[index] + 1;
    lst->prev[index] = FREE_label;


    return NO_ERROR;
}


// int ListPushEnd(LIST* lst, List_t element)
// {
//     assert(lst);
//
//     double sell = 0;
//     if(StackPop(&lst->free_stk, &sell) == STACK_UNDERFLOW)
//     {
//         return LIST_OVERFLOW;
//     }
//
//     lst->data[lst->size] = element;
//
//     lst->prev[lst->capacity - 1] = (int)sell;
//     lst->next[lst->size]         = lst->capacity - 1;
//     lst->next[(int)sell]         = lst->size;
//
//     ++lst->size;
//     return NO_ERROR;
// }




int ListDtor(LIST* lst)
{
    assert(lst);

    StackDtor(&lst->free_stk);
    free(lst->data);
    free(lst->next);
    free(lst->prev);

    return NO_ERROR;
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



