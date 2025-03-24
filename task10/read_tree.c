#include "bul.func.h"

struct NODE* create_tree(struct CONVERSIONS* conversion)
{
    struct NODE* root;
    root = GetG(conversion);
    return root;
}

void spend(struct NODE* node)
{
    if (node->left != NULL) spend(node->left);
    if (node->right != NULL) spend(node->right);
}

struct NODE* GetH(struct CONVERSIONS* conversion)
{
    struct NODE* val = GetF(conversion);
    while (conversion->s[conversion->p] == '~')
    {
        conversion->p++;

        struct NODE* val_2 = GetF(conversion);
        union values value;
        value.sym_value = EQV;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

struct NODE* GetF(struct CONVERSIONS* conversion)
{
    struct NODE* val = GetE(conversion);
    while (conversion->s[conversion->p] == '-')
    {
        conversion->p++;

        struct NODE* val_2 = GetH(conversion);
        union values value;
        value.sym_value = IMP;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

struct NODE* GetP(struct CONVERSIONS* conversion)
{
    if (conversion->s[conversion->p] == '(')
    {
        conversion->p++;

        struct NODE* val = GetH(conversion);
        if (conversion->s[conversion->p] != ')')
        {
            SyntaxERROR(ERROR_P);
        }

        conversion->p++;

        return val;
    }
    else
    {
        return GetV(conversion);
    }

}

struct NODE* GetE(struct CONVERSIONS* conversion)
{
    struct NODE* val = GetT(conversion);
    while (conversion->s[conversion->p] == '+')
    {
        conversion->p++;

        struct NODE* val_2 = GetT(conversion);
        union values value;
        value.sym_value = ADD;
        val = new_node(SYM, value, val, val_2);

    }

    return val;
}

struct NODE* GetN(struct CONVERSIONS* conversion)
{

    if ('A' - 1 < conversion->s[conversion->p] && conversion->s[conversion->p] < 'Z' + 1)
    {
        union values value;
        value.var_value = conversion->s[conversion->p];

        struct NODE* val = new_node(VAR, value, NULL, NULL);
        conversion->p++;
        return val;
    }
    else
    {
        SyntaxERROR(ERROR_N);
        return NULL;
    }

}

struct NODE* GetT(struct CONVERSIONS* conversion)
{
    struct NODE* val = GetP(conversion);
    while (conversion->s[conversion->p] == '*')
    {
        conversion->p++;
        struct NODE* val_2 = GetP(conversion);
        union values value;
        value.sym_value = MUL;
        val = new_node(SYM, value, val, val_2);
    }
    return val;
}

struct NODE* GetG(struct CONVERSIONS* conversion)
{
    struct NODE* val = GetH(conversion);
    if (conversion->s[conversion->p] == '$')
    {
        conversion->p++;
        return val;
    }
    else
    {
        SyntaxERROR(ERROR_G);
        return NULL;
    }
}

struct NODE* GetV(struct CONVERSIONS* conversion)
{
    if (conversion->s[conversion->p] == '!')
    {
        union values value;
        value.sym_value = NOT;
        conversion->p++;
        struct NODE* val = new_node(SYM, value, GetN(conversion), NULL);

        return val;
    }
    else
    {
        return GetN(conversion);
    }

}


void  SyntaxERROR(int code_error)
{
    fprintf(stderr, "ERROR %d", code_error);
    exit(0);
}

struct NODE* new_node(int type, union values value, struct NODE* vol, struct NODE* vol2)
{
   struct NODE*  node = (struct NODE*) calloc(1, sizeof(struct NODE));
   node->type  = type;
   node->value = value;
   node->left  = vol;
   node->right = vol2;
   return node;
}
