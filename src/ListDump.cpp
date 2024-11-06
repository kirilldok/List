#include "ListFunc.h"

const char *LIST_LOG_FILE   = "run/Listlog.html";
const char *LIST_GRAPHVIZ   = "run/graphviz.gv";
const char *SYSTEM_CMD_LINE = "dot -Tpng run/graphviz.gv -o run/graphviz/graphviz";
const char *HTML_MAKE_IMG   = "<img src =\"run/graphviz/graphviz";
const int   LIST_CMD_SIZE   = 128;

int ListDump(LIST* lst)
{
    assert(lst);

    FILE* logfile = fopen(LIST_LOG_FILE, "a+"); assert(logfile);

    fprintf(logfile, "<pre>\n");
    fprintf(logfile, "#####################LISTDUMP#####################\n");
    fprintf(logfile,
            "## LIST SIZE:     %lu\n"
            "## LIST CAPACITY: %lu\n"
            /*"## LIST HEAD:     %d\n"
            "## LIST TAIL:     %d\n"*/,
            lst->size, lst->capacity/*, lst->head, lst->tail*/);

    fprintf(logfile, "\t");
    for(size_t i = 0; i < lst->capacity; i++)
    {
        fprintf(logfile, "%.2lu ", i);
    }
    fprintf(logfile, "\n");
    //fprintf(stderr, "cap = %d\n", lst->capacity);
    PrintArray(lst->data, sizeof(List_arg_t), lst->capacity, logfile);
    PrintArray(lst->next, sizeof(size_t), lst->capacity, logfile);
    PrintArray(lst->prev, sizeof(size_t), lst->capacity, logfile);


    FILE* graffile = fopen(LIST_GRAPHVIZ, "w+"); assert(graffile);
    MakeDotFile(lst, graffile);
    fclose(graffile);


    static int cntImg = 1;
    char *str = (char*)calloc(LIST_CMD_SIZE, sizeof(char));

    sprintf(str, "%s%d%s", SYSTEM_CMD_LINE, cntImg, ".png");
    system(str);
    sprintf(str, "%s%d%s", HTML_MAKE_IMG, cntImg, ".png\">\n");

    fprintf(logfile, "%s", str);
    cntImg = cntImg + 1;
    free(str);

    fprintf(logfile, "##################################################\n");
    fclose(logfile);

    return NO_ERRORS;
}


int MakeDotFile(LIST* lst, FILE* graffile)
{
    assert(lst); assert(graffile);

    fprintf(graffile,
            "digraph List \n{\n"
            "\trankdir = LR;\n"
            "\tbgcolor = \"#412FC6\"\n\n");
    fprintf(graffile, //printing ferst null element
                "\tnode000 ["
                "shape = \"Mrecord\"; "
                "style = \"filled\"; "
                "color = \"#A51FE0\"; "
                "label = \""
                "{ ip: 000} | "
                "{data: %d} | "
                "{next: %lu} | "
                "{prev: %lu} \" ];\n", lst->data[0], lst->next[0], lst->prev[0]);

    for(size_t i = 1; i < lst->capacity; i++) //making order of list elements
    {
        fprintf(graffile,
                "\tnode%.3lu ["
                "shape = \"Mrecord\"; "
                "style = \"filled\"; "
                "color = \"#807E97\"; "
                "label = \""
                "{ ip: %.3lu} | "
                "{data: %d} | "
                "{next: %lu} | "
                "{prev: %lu} \" ];\n", i, i, lst->data[i], lst->next[i], lst->prev[i]);
    }

    fprintf(graffile, "\n");

    for(size_t i = 1; i < lst->capacity; i++) //printing  elements in order
    {
        fprintf(graffile,
                "\tnode%.3lu -> "
                "node%.3lu ["
                "style = bold; "
                "weight = 10000; "
                "color = yellow1; ];\n"
                ,i-1,i);
    }

    fprintf(graffile, "\n");

    for(size_t i = 0; i < lst->capacity; i++) //printing prev elemens order
    {
        if(lst->prev[i] == FREE_label)
        {
            fprintf(graffile,
                    "\tnode%.3lu ["
                    "weight = 0; "
                    "constraint = false; "
                    "color  = red; ];\n", i);
        }

        else if(i != lst->prev[lst->next[i]])
        {
            fprintf(graffile,
                "\tnode%.3lu -> "
                "node%.3lu ["
                "weight = 0; "
                "constraint = false; "
                "color  = red1; ];\n", i, lst->next[i]);
        }

        else if(i != lst->next[lst->prev[i]])
        {
            fprintf(graffile,
                    "\tnode%.3lu -> "
                    "node%.3lu ["
                    "weight = 0; "
                    "constraint = false; "
                    "color  = orange2; ];\n", i, lst->prev[i]);
        }

        else
        {
            fprintf(graffile,
                    "\tnode%.3lu -> "
                    "node%.3lu ["
                    "dir = both; "
                    "arrowtail = crow; "
                    "weight = 0; "
                    "constraint = false; "
                    "color  = green2; ];\n", i, lst->next[i]);
        }
    }

    fprintf(graffile, "\n");

    fprintf(graffile, "}\n");

    return NO_ERRORS;
}


int PrintArray(void* Arr, size_t elsize, size_t capacity, FILE* file)
{
    assert(Arr); assert(file);

    fprintf(file, "\t");
    for(size_t i = 0; i < capacity; i++)
    {
        fprintf(file, "%.2d ", *((char*)Arr + i * elsize));
    }
    fprintf(file, "\n");

    return NO_ERRORS;
}
