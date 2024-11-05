#include "ListFunc.h"


int main()
{
    LIST lst = { 0 };

    ListCtor(&lst, 8);
    ListDump(&lst);

    ListPushInd(&lst, 10, 0);
    ListDump(&lst);
    ListPushInd(&lst, 20, 1);
    ListDump(&lst);
    ListPushInd(&lst, 30, 2);
    ListDump(&lst);
    ListPushInd(&lst, 40, 3);
    ListDump(&lst);
    ListPushInd(&lst, 50, 4);
    ListDump(&lst);
    ListPushInd(&lst, 25, 2);
    ListDump(&lst);
    List_t x = 0;
    ListPopInd(&lst, &x, 3);
    ListDump(&lst);
    fprintf(stderr, "x = %d\n", x);

    ListDtor(&lst);

    return 0;
}
