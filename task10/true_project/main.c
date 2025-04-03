#include "bul.h"

int main()
{
    struct CONVERSIONS* conversion = make_conversion();
    struct tokens_t* arr_token = create_lec(conversion);
    struct NODE* root = create_tree(conversion, arr_token);
    DrawTree(root);
    amount_var(root, conversion);
    printf("amount Var: %d\n",  conversion->amount_var);


    struct var_t* mas_var = create_var(conversion);

    for (int i = 0; i < conversion->amount_var; i++)
    {
        printf(" %c %d \n", mas_var[i].name_var, mas_var[i].definition_var);
    }

    root = substitute_value(root, mas_var, conversion);
    DrawTree(root);
    root = calculation(root);
    printf("ANSWER: %d", root->value);

    return 1;
}