#include "ListFunc.h"

const char *LIST_LOG_FILE = "../run/Listlog.html";
const char *LIST_GRAPHVIZ = "../run/graphviz.gv";
const int   LIST_CMD_SIZE = 256;

int ListDump(LIST* lst)
{
    assert(lst);

    FILE* logfile = fopen(LIST_LOG_FILE, "a"); assert(logfile);

    fprintf(logfile, "<pre>\n");
    fprintf(logfile, "#####################LISTDUMP#####################\n");
    fprintf(logfile,
            "## LIST SIZE:     %d\n",
            "## LIST CAPACITY: %d\n",
            "## LIST HEAD:     %d\n",
            "## LIST TAIL:     %d\n",
            lst->size, lst->capacity, lst->head, lst->tail);

    fprintf(logfile, "\t");
    for(int i = 0; i < lst->capacity; i++)
    {
        fprintf(logfile, "%.2d ", i);
    }
    fprintf(logfile, "\n");

    PrintArray(lst->data, lst->capacity, logfile);
    PrintArray(lst->next, lst->capacity, logfile);
    PrintArray(lst->prev, lst->capacity, logfile);

    FILE* graffile = fopen(LIST_GRAPHVIZ, "w"); assert(graffile);
    MakeDotFile(lst, graffile);
    fclose(graffile);

    static int cntImg = 1;
    char *str = (char*)calloc(LIST_CMD_SIZE, sizeof(char));

    sprintf(str, "%s%d%s", "dot -Tpng ../run/graphviz.gv -o ../res/graphviz/graphviz", cntImg, ".png");
    system(str);
    sprintf(str, "%s%d%s", "<img src =\"../run/graphviz/graphviz", cntImg, ".png\"><br>");

    fprintf(logfile, "%s", str);
    cntImg = cntImg + 1;
    free(str);

    fclose(logfile);

    return NO_ERRORS;
}


int MakeDotFile(LIST* lst, FILE* graffile)
{
    assert(lst); assert(graffile);

    fprintf(graffile,
            "digraph List \n{\n"
            "\trankdir = LR;\n"
            "\tbgcolor = \"#807E97\"\n");

    size_t capacity = sizeof(lst->data) / sizeof(lst->data[0]); assert(capacity);
    for(int i = 0; i < capacity; i++) //making order of list elements
    {
        fprintf(graffile,
                "node%.3d ["
                "shape = Mrecord; "
                "stile = filled; "
                "color = \"#5645D1\"; "
                "lable = \""
                "{ ip: %.3d} | "
                "{data: %d} | "
                "{next: %d} | "
                "{prev: %d} \" ]\n", i, i, lst->data[i], lst->next[i], lst->prev[i]);
    }

    for(int i = 1; i < capacity; i++)
    {
        fprintf(graffile,
                "\tnode%.3d -> "
                "node%.3d ["
                "style = bold; "
                "weight = 1000; "
                "color = crimson; ];\n"
                ,i-1,i);
    }

    for(int i = 0; i < lst->size; i++)
    {
        fprintf(graffile,
                "\tnode%.3d -> "
                "node%.3d ["
                "weight = 0; "
                "color = yellow1; ];\n", lst->next[i], lst->next[i + 1]);
    }

    for(int i = lst->size; i > 0; i--)
    {
        fprintf(graffile,
                "\tnode%.3d -> "
                "node%.3d ["
                "weight = 0; "
                "color = purple; ];\n", lst->prev[i] , lst->prev[i - 1]);
    }

    fprintf(graffile, "}\n");

    return NO_ERRORS;
}


int PrintArray(List_t* Arr, int capacity, FILE* file)
{
    assert(Arr); assert(file);

    fprintf(file, "\t");
    for(int i = 0; i < capacity; i++)
    {
        fprintf(file, "%.2d ", Arr[i]);
    }
    fprintf(file, "\n");

    return NO_ERRORS;
}
