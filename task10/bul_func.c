#include "bul.func.h"



int main()
{
    struct CONVERSIONS* conversion = make_conversion();
    struct NODE* root = create_tree(conversion);


    amount_var(root, conversion);


    struct var_t* mas_var = create_var(conversion);

    for (int i = 0; i < conversion->amount_var; i++)
    {
        printf(" %c %d \n", mas_var[i].name_var, mas_var[i].definition_var);
    }

    DrawTree(root);
    root = substitute_value(root, mas_var, conversion);
    root = decision(root);

    
    printf("ANSWER: %d", root->value.num_value);
}


struct CONVERSIONS* make_conversion()

{
    struct CONVERSIONS* conversion = (struct CONVERSIONS*) calloc(1, sizeof(struct CONVERSIONS));
    conversion->p = 0;
    conversion->amount_var = 0;
    FILE* file_in = fopen("task.txt", "r");
    int amount_scanf = fscanf(file_in, "%s",conversion->s);
    if (amount_scanf == 0)
    {
        fprintf(stderr,"ERROR in make_conversion, the function was not read");
    }
    fclose(file_in);
    return conversion;
}

void amount_var(struct NODE* node, struct CONVERSIONS* conversion)
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

struct var_t* create_var(struct CONVERSIONS* conversion)
{
    struct var_t* mas_var = (struct var_t*) calloc(conversion->amount_var, sizeof(struct var_t));
    
    int i = 0;
    int j = 0;
    while (conversion->s[j] != '$')
    {
        if (conversion->s[j] >= 'A' && conversion->s[j] <= 'Z')
        {
            printf("Enter a value for the variable: %c\n", conversion->s[j]);
            int scanf_amount = scanf("%d", &mas_var[i].definition_var);
            while (scanf_amount != 1)
            {
                printf("Enter correct value\n");
                clear_input_buffer();
                scanf_amount = scanf("%d",&mas_var[i].definition_var);
            }
            while (mas_var[i].definition_var != 1 && mas_var[i].definition_var != 0)
            {
                printf("The variable value can be 0 or 1, please enter the correct value.\n");
                clear_input_buffer();
                scanf_amount = scanf("%d",&mas_var[i].definition_var);
            }
            mas_var[i].name_var = conversion->s[j];
            i++;
                
        }
        j++;
    }
    return mas_var;
   
}
void clear_input_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

struct NODE* substitute_value(struct NODE* node, struct var_t* mas_var, struct CONVERSIONS* conversion)
{

    if (node->type == VAR)
    {
        for (int i = 0; i < conversion->amount_var; i++)
        {
            if(node->value.var_value == (int) mas_var[i].name_var)
            {
                union values value;
                value.num_value = mas_var[i].definition_var;
                node->type = NUM;
                node->value = value;
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

struct NODE* decision(struct NODE* node)
{
    if (node->type == NUM)
    {
        return node;
    }
    else
    {
        switch(node->value.sym_value)
        {
            case NOT:
            {
                node->type = NUM;
                int val = node->left->value.num_value;
                if (val == 0) node->value.num_value = 1;
                if (val == 1) node->value.num_value = 0;

                break;
            }
            case MUL:
            {
                node->left = decision(node->left);
                node->right = decision(node->right);
                int val2 = node->right->value.num_value;
                int val1 = node->left->value.num_value;
                union values value;
                value.num_value = val1 * val2;
                node->type = NUM;
                node->value = value;
                break;
            }
            case IMP:
            {
                decision(node->left);
                decision(node->right);

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
                
                break;
            }
            case ADD:
            {
                decision(node->left);
                decision(node->right);

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
                
                break;
            }
            case EQV:
            {
                decision(node->left);
                decision(node->right);

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
               
                break;
            }

            default:
            {
                fprintf(stderr, "Error: unknown operation(%d)", node->value.sym_value);
                return NULL;
            }
        }
    return node;
    }

}


struct NODE* copy_node(struct NODE* node)
{
    if (!node)
    {
        return NULL;
    }

    struct NODE* copynode =  new_node(node->type, node->value, copy_node(node->left), copy_node(node->right));

    return copynode;

}






