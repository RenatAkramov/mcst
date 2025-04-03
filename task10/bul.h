#ifndef differentiator_h
#define differentiator_h
#define amount_operations 6
#define max_variable 28

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>



struct CONVERSIONS
{
    char* s;
    int p;
    int amount_var;
};

union values
{
    int num_value;
    int var_value;
    int oper_value;
};

typedef struct {
    char name;
    int value;
} Variable;

struct NODE
{
    int type;
    
    union values value;
    struct NODE* left;
    struct NODE* parent;
    struct NODE* right;
};

struct tokens_t
{
    int type;
    union values value;
    char* name;
    struct NODE* node;
};



enum type
{
    OPER  = 1,
    VAR   = 2,
    NUM   = 3,
    END   = 4,
    bracket_left  = 5,
    bracket_right = 6,
};
enum operations
{
    AND  = 7,
    NOT  = 8,
    OR   = 9,
    IMP  = 10,
    XOR  = 11,
    XNOR = 12,
};






struct operations_t
{
    char* name_symbol;
    int code;
};

enum errorcode
{
    ERROR_H = 0,
    ERROR_F = 1,
    ERROR_X = 2,
    ERROR_E = 3,
    ERROR_T = 4,
    ERROR_P = 5,
    ERROR_V = 6,
    ERROR_N = 7,
    ERROR_G = 8
};

struct var_t
{
    char name_var;
    int definition_var;
};

extern const struct operations_t operations[];

struct FUNKTION_T
{
    const char* name;
    int code;
};



struct CONVERSIONS* make_conversion();
struct tokens_t* create_lec(struct CONVERSIONS* conversion);
int    create_tokens(int len_buf, struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* create_tree(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
void   spend(struct NODE* node);
struct NODE* GetP(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetX(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetN(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetF(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* copy_node(struct NODE* node);
struct NODE* GetH(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetG(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetE(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetT(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
void   SyntaxERROR(int errorcode);
struct NODE* new_node(int type, union values value, struct NODE* vol, struct NODE* vol2);
struct NODE* GetV(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
int    DrawTree(struct NODE* root);
int    DrawNode(struct NODE* node, FILE* file_ptr);
void   amount_var(struct NODE* node, struct CONVERSIONS* conversion);
struct var_t* create_var(struct CONVERSIONS* conversion);
struct NODE* substitute_value(struct NODE* node,struct var_t* mas_var,struct CONVERSIONS* conversion);
struct NODE* calculation(struct NODE* node);
void print_truth_table(struct NODE* root);
void collect_variables(struct NODE* node, Variable* vars, int* count); 

int evaluate(struct NODE* node, Variable* vars, int var_count);

/*
struct NODE* diff(struct NODE* node);
struct NODE* simplifare(struct NODE* node, struct NODE* root);

struct NODE* GetC(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
unsigned long long hash_func(int val, struct NODE* node);
void hash_all(struct NODE* val);
int print_node(struct NODE* node, FILE* file_l);
void create_latex_simplifare_diff(struct NODE* root);*/


#endif
