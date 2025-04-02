#include "bul.h"

int main()
{
    struct CONVERSIONS* conversion = make_conversion();
    struct tokens_t* arr_token = create_lec(conversion);
    struct NODE* root = create_tree(conversion, arr_token);

    return 1;
}