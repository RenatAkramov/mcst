#include "bul.func.h"

static const struct operations_t operations[amount_operations] = {{'*', MUL}, {'!', NOT}, {'+', ADD},{'~', EQV}, {'-', IMP}};

int DrawTree(struct NODE* root)
{
    if (!root)
    {
        fprintf(stderr, "Drawing error: root(%p)\n", (void*) root);
        return -1;
    }

    FILE* file_ptr = fopen("grafdump.dot", "w");

    if (!file_ptr)
    {
        fprintf(stderr, "File \"grafdump.dot\" error!\n");
        return -1;
    }

    fprintf(file_ptr, "digraph G\n{\n  rankdir = UD;\n  edge[color = \"green\"];\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}");

    fclose(file_ptr);

    int status = system("dot grafdump.dot -Tpng -o Dump.png");
    if (status != 0) 
    {
        fprintf(stderr, "Graph generation error. Code:%d\n", status);
        
        
    }
    return 0;
}

int DrawNode(struct NODE* node, FILE* file_ptr)
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return -1;
    }

    fprintf(file_ptr, "  \"%p\" [shape = Mrecord, ",(void*) node);

    if (!node->left && !node->right)
    {
        fprintf(file_ptr, "color = \"limegreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", ");
    }
    else
    {
        fprintf(file_ptr, "color = \"khaki3\", style = \"filled\", fillcolor = \"lemonchiffon\", ");
    }


    fprintf(file_ptr, "label = \"");
    if (node->type == NUM)
    {
        fprintf(file_ptr,  "%1d", node->value.num_value);
    }
    else if (node->type == VAR)
    {
        fprintf(file_ptr,  "%c", node->value.var_value);
    }
    else if(node->type == SYM)
    {
        for (int i = 0; i < amount_operations; ++i)
        {
            if (node->value.sym_value == operations[i].code)
            {
                fprintf(file_ptr, "%c", operations[i].name_symbol);

                break;
            }
        }
    }

    fprintf(file_ptr, "\"];\n");

    if (DrawNode(node->left,  file_ptr) != 0) return -1;
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n",(void*) node,(void*) node->left);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n",(void*) node,(void*) node->right);
    }

    return 0;
}
