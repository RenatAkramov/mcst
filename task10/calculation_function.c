#include "bul.h"


void amount_var(struct NODE* node,struct CONVERSIONS* conversion)
{
    if (node->type == VAR)
    {
        conversion->amount_var++;
    }
    if (node->right != NULL)
    {
        amount_var(node->right, conversion);
    }
    if (node->left != NULL)
    {
        amount_var(node->left, conversion);
    }
}

struct NODE* substitute_value(struct NODE* node, struct var_t* mas_var,struct  CONVERSIONS* conversion)
{

    if (node->type == VAR)
    {
        printf("In var\n");
        for (int i = 0; i < conversion->amount_var; i++)
        {
            if(node->value.var_value == (int) mas_var[i].name_var)
            {
                union values value;
                value.num_value = mas_var[i].definition_var;
                node->type = NUM;
                printf("In var after num %c %d\n", mas_var[i].name_var, mas_var[i].definition_var);
                node->value = value;
                printf("In var after val %d\n", node->value.num_value);
            }
        }
    }

    if (node->right != NULL)
    {
        substitute_value(node->right, mas_var, conversion);
    }
    if (node->left != NULL)
    {
        substitute_value(node->left, mas_var, conversion);
    }
    return node;
}

struct NODE* calculation(struct NODE* node)
{
    if (node->type == NUM)
    {
        return node;
    }
    else
    {
        switch(node->value.oper_value)
        {
            case NOT:
            {
                printf("in NOT\n");
                node->type = NUM;
                int val = node->left->value.num_value;
                if (val == 0) node->value.num_value = 1;
                if (val == 1) node->value.num_value = 0;
                printf(" NOT:: val1 = %d, all val = %d\n", val, node->value.num_value);

                break;
            }
            case AND:
            {
                printf("in MUL\n");
                node->left = calculation(node->left);
                node->right = calculation(node->right);
                printf("after calculation in mul\n");
                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                printf("mul after val1 val2\n");
                union values value;
                value.num_value = val1 * val2;
                node->type = NUM;
                node->value = value;
                printf(" MUL:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case IMP:
            {
                printf("in IMP\n");
                calculation(node->left);
                calculation(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                union values value;
                if (val1 == 1 && val2 == 0)
                {
                    value.num_value = 0;
                }
                else
                {
                    value.num_value = 1;
                }
                node->type = NUM;
                node->value = value;
                printf(" IMP:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case OR:
            {
                printf("in ADD\n");
                calculation(node->left);
                calculation(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                union values value;
                if (val1 == 0 && val2 == 0)
                {
                    value.num_value = 0;
                }
                else
                {
                    value.num_value = 1;
                }
                node->type = NUM;
                node->value = value;
                printf(" ADD:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }
            case XNOR:
            {
                printf("in EQV\n");
                (node->left);
                calculation(node->right);

                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                union values value;
                if (val1 == val2)
                {
                    value.num_value = 1;
                }
                else
                {
                    value.num_value = 0;
                }
                node->type = NUM;
                node->value = value;
                printf(" EQV:: val1 = %d, val2 = %d, all val = %d\n", val1, val2, node->value.num_value);

                break;
            }

            default:
            {
                fprintf(stderr, "ERROR: unknown operation value: %d, type: %d\n", node->value.oper_value, node->type);
                return NULL;
            }
        }
    return node;
    }
}

struct var_t* create_var(struct CONVERSIONS* conversion)
{
    struct var_t* mas_var = (struct var_t*) calloc(conversion->amount_var, sizeof(struct var_t));
    char name;
    for (int i = 0; i < conversion->amount_var; i++)
    {
        printf("Enter name definition\n");
        scanf("%c", &mas_var[i].name_var );
        printf("Enter definition\n");
        int def = -1;
        scanf("%d", &def);
        while (def > 1 || def < 0)
        {
            printf("your defifinition can be 0 or 1 Please enter definition\n");
            scanf("%d", &def);
        }

        mas_var[i].definition_var = def;
      

    }
    return mas_var;
}

struct NODE* copy_node(struct NODE* node)
{
    if (!node)
    {
        fprintf(stderr, "ERROR: erorr copy_node\n");
        return NULL;
    }

    struct NODE* copynode =  new_node(node->type, node->value, copy_node(node->left), copy_node(node->right));

    return copynode;
}