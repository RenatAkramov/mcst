#ifndef differentiator_h
#define differentiator_h

#include <stdio.h>
#include <stdlib.h>

struct NODE;
struct CONVERSIONS
{
    char s[999];
    int p;
    int amount_var;
};

union values
{
    int num_value;
    int var_value;
    int sym_value;
};

struct NODE
{
    int type;
    union values value;
    struct NODE* left;
    struct NODE* parent;
    struct NODE* right;
};

enum operations
{
    MUL = 1,
    NOT = 2,
    ADD = 3,
    IMP = 4,
    EQV = 5,
};


#define amount_operations 5

struct var_t
{
    char name_var;
    int definition_var;
};

enum type
{
    SYM  = 1,
    VAR  = 2,
    NUM  = 3
};

struct operations_t
{
    char name_symbol;
    int code;
};

enum errorcode
{
    ERROR_E = 0,
    ERROR_P = 1,
    ERROR_V = 2,
    ERROR_T = 3,
    ERROR_G = 4,
    ERROR_N = 5,
    ERROR_F = 6,
    ERROR_H = 7
};

//struct operations_t operations[amount_operations] = {{'*', MUL}, {'!', NOT}, {'+', ADD},{'~', EQV}, {'-', IMP}};




struct NODE* new_node(int type, union values value, struct NODE* vol, struct NODE* vol2);

struct NODE* create_tree(struct CONVERSIONS* conversion);

struct NODE* GetP(struct CONVERSIONS* conversion);
struct NODE* GetE(struct CONVERSIONS* conversion);
struct NODE* GetT(struct CONVERSIONS* conversion);
struct NODE* GetG(struct CONVERSIONS* conversion);
struct NODE* GetN(struct CONVERSIONS* conversion);
struct NODE* GetF(struct CONVERSIONS* conversion);
struct NODE* GetH(struct CONVERSIONS* conversion);
void  SyntaxERROR(int code_error);
struct NODE* GetV(struct CONVERSIONS* conversion);
void  spend(struct NODE* node);
int   DrawTree(struct NODE* root);
int   DrawNode(struct NODE* node, FILE* file_ptr);
struct CONVERSIONS* make_conversion();
struct NODE* copy_node(struct NODE* node);
void amount_var(struct NODE* node, struct CONVERSIONS* conversion);
struct var_t* create_var(struct CONVERSIONS* conversion);
struct NODE* substitute_value(struct NODE* node, struct var_t* mas_var, struct CONVERSIONS* conversion);
struct NODE* decision(struct NODE* node);
void clear_input_buffer();



#endif
