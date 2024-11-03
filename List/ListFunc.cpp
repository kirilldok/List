#include"ListFunc.h"

static const int Poison_lable = -666;

int ListCtor(LIST* lst, int size)
{
    assert(lst);

    lst->data    = (List_t*)calloc(size, sizeof(List_t)); assert(lst->data);
    lst->next    = (List_t*)calloc(size, sizeof(List_t)); assert(lst->next);
    lst->prev    = (List_t*)calloc(size, sizeof(List_t)); assert(lst->prev);

    lst->capacity = size;
    lst->data[0] = START_OF_LABLE;
    lst->data[1] = END_OF_LABLE;
    lst->next[0] = 0;
    lst->prev[0] = 0;
    lst->size    = 2;

    lst->head    = START_HEAD;
    lst->tail    = START_TAIL;

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
        lst->next[i] = Poison_lable;
        lst->prev[i] = Poison_lable;
    }

    return NO_ERRORS;
}

int GetFirstPTR(LIST* lst)
{
    assert(lst);
    int i = 0;
    while(lst->prev[i] == 0)
        ++i;

    return lst->prev[i];
}


int ListPush(LIST* lst, List_t element, int index) // add an element after input index
{
    assert(lst);

    int sell  = 0;
    if ((sell = FindFreeSell(lst->next, lst->capacity)) == LIST_OVERFLOW)
    {
       fprintf(stderr, "NO free sells!\n");
        return LIST_OVERFLOW;
    }

    lst->data[lst->size] = element;
    ++lst->size;

    lst->next[sell] = index + 1;
    lst->next[index + 1] = lst->size;


    if ((sell = FindFreeSell(lst->prev, lst->capacity)) == LIST_OVERFLOW)
    {
       fprintf(stderr, "NO free sells!\n");
        return LIST_OVERFLOW;
    }

    lst->prev[sell] = index;
    lst->prev[index] = lst->size;

    return NO_ERRORS;
}


int Listappend(LIST* lst, List_t element)
{
    assert(lst);

    if (lst->head >= lst->size)
    {
        fprintf(stderr, "List overflow! Element %d will not be written!\n", element);
        return LIST_OVERFLOW;
    }

    if ((lst->head == START_HEAD) && (lst->size == 0))
    {
        lst->data[START_HEAD] = element;
        lst->prev[START_HEAD] = END_OF_LABLE;
        ++lst->size;
        ++lst->head;
        return NO_ERRORS;
    }

    // int sell = 0;
    // if ((sell = FindFreeSell(lst)) == LIST_OVERFLOW)
    // {
    //    fprintf(stderr, "NO free sells!\n");
    //     return LIST_OVERFLOW;
    // }

    lst->data[lst->size]     = element;
    lst->next[lst->head - 1] = lst->head;
    lst->next[lst->head + 1] = END_OF_LABLE;
    lst->prev[lst->head]     = lst->head - 1;

    ++lst->head;
    ++lst->tail;

    return NO_ERRORS;
}


int FindFreeSell(List_t* arr, int capacity)
{
    assert(arr);

    for(int i = START_HEAD; i < capacity; i++)
    {
        if( arr[i] == Poison_lable)
        {
            return i;
        }
    }

    return LIST_OVERFLOW;
}



int ListDtor(LIST* lst)
{
    assert(lst);

    free(lst->data);
    free(lst->next);
    free(lst->prev);

    return NO_ERRORS;
}


