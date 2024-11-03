#include <stdio.h>
#include "List/ListFunc.h"


int main()
{
    LIST lst = { 0 };

    ListCtor(&lst, 16);
    ListDump(&lst);
    ListDtor(&lst);

    return 0;
}
