#include "ListFunc.h"


int main()
{
    LIST lst = { 0 };

    ListCtor(&lst, 8);
    ListDump(&lst);

    ListPush(&lst, 10, 0);
    ListDump(&lst);
    ListPush(&lst, 20, 1);
    ListDump(&lst);
    ListPush(&lst, 30, 2);
    ListDump(&lst);
    ListPush(&lst, 40, 3);
    ListDump(&lst);
    ListPush(&lst, 50, 4);
    ListDump(&lst);
    ListPush(&lst, 25, 2);
    ListDump(&lst);

    ListDtor(&lst);

    return 0;
}
