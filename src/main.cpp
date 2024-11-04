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
    ListDtor(&lst);

    return 0;
}
