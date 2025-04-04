#include "bul.h"

int main()
{
    struct CONVERSIONS* conversion = make_conversion();
    assert(conversion);
    struct tokens_t* arr_token = create_lec(conversion);
    assert(arr_token);
    struct NODE* root = create_tree(conversion, arr_token);
    DrawTree(root);

    print_truth_table(root);

    return 1;
}