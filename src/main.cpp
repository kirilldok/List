#include "ListFunc.h"


int main()
{
    LIST lst = { 0 };

    ListCtor(&lst, 10);
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

    // lst.next[2] = 0;
    // ListDump(&lst);


    ListPopInd(&lst, 3);
    ListDump(&lst);

    ListDtor(&lst);

    return 0;
}
