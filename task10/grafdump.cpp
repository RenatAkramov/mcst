#include "differentiator.h"

int DrawTree(NODE* root)
{
    printf("in draw\n");
    if (!root)
    {
        fprintf(stderr, "Drawing error: root(%p)\n", root);
        return -1;
    }

    FILE* file_ptr = fopen("grafdump.dot", "w");

    if (!file_ptr)
    {
        fprintf(stderr, "File \"grafdump.dot\" error!\n");
        return -1;
    }
    printf("erglifdkn\n");
    fprintf(file_ptr, "digraph G\n{\n  rankdir = UD;\n  edge[color = \"green\"];\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}");

    fclose(file_ptr);

    system("dot grafdump.dot -Tpng -o Dump.png");
    printf("after dot\n");
    return 0;
}

int DrawNode(NODE* node, FILE* file_ptr)
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return -1;
    }

    fprintf(file_ptr, "  \"%p\" [shape = Mrecord, ", node);

    if (!node->left && !node->right)
    {
        fprintf(file_ptr, "color = \"limegreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", ");
    }
    else
    {
        fprintf(file_ptr, "color = \"khaki3\", style = \"filled\", fillcolor = \"lemonchiffon\", ");
    }


    fprintf(file_ptr, "label = \"");
    //printf("NODE TYPE: %d\n", node->type);
    if (node->type == VAR)
    {
        //printf("IN var\n");
        fprintf(file_ptr,  "%c", 'x');
    }
    else if (node->type == NUM)
    {
        //printf("in NUM\n");
        fprintf(file_ptr, "%d", node->value.num_value);
    }
    else if (node->type == SYM)
    {
        //printf("in SYM\n");
        for (int i = 0; i < amount_operations; ++i)
        {
            if (node->value.sym_value == operations[i].code)
            {
                fprintf(file_ptr, "%c", operations[i].name_symbol);

                break;
            }
        }
    }
    else if (node->type == FUN)
    {
        //printf("in FUN\n");
        for (int i = 0; i < amount_fun; ++i)
        {
            if (node->value.fun_value == funktions[i].code)
            {
                fprintf(file_ptr, "{%s}", funktions[i].name);
                break;
            }
        }
    }

    fprintf(file_ptr, "|{%d |  %llx} \"];\n",node->type, node-> hash);

    if (DrawNode(node->left,  file_ptr) != 0) return -1;
    if (DrawNode(node->right, file_ptr) != 0) return -1;

    if (node->left)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n", node, node->left);
    }

    if (node->right)
    {
        fprintf(file_ptr, "  \"%p\" -> \"%p\";\n", node, node->right);
    }

    return 0;
}
