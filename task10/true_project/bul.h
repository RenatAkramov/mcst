#ifndef differentiator_h
#define differentiator_h
#define amount_operations 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdint.h>



struct CONVERSIONS
{
    char* s;
    int p;
};

union values
{
    int num_value;
    int var_value;
    int oper_value;
};

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
    AND  = 1,
    NOT  = 2,
    OR   = 3,
    IMP  = 4,
    XOR  = 5,
    XNOR = 6
};

enum hsh
{
    OKEY = 1,
    ERRORS = 0
};




struct operations_t
{
    char* name_symbol;
    int code;
};

enum errorcode
{
    ERROR_E = 0,
    ERROR_P = 1,
    ERROR_N = 2,
    ERROR_T = 3,
    ERROR_G = 4
};

//const struct operations_t operations_[amount_operations] = {{"AND", AND}, {"OR", OR}, {"NOT", NOT}, {"XOR", XOR}, {"IMP", IMP}, {"XNOR", XNOR}};

struct FUNKTION_T
{
    const char* name;
    int code;
};



struct CONVERSIONS* make_conversion();
struct tokens_t* create_lec(struct CONVERSIONS* conversion);
int create_tokens(int len_buf, struct CONVERSIONS* conversion, struct tokens_t* arr_token);

/*struct NODE* new_node(int type, union values value, struct NODE* vol, struct NODE* vol2);
struct NODE* create_tree(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetP(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetE(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetT(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetG(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* GetN(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
void  SyntaxERROR();
struct NODE* GetV(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
void  spend(struct NODE* node);
int   DrawTree(struct NODE* root);
int   DrawNode(struct NODE* node, FILE* file_ptr);
struct CONVERSIONS* make_conversion();
struct NODE* GetF(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
struct NODE* copy_node(struct NODE* node);
struct NODE* diff(struct NODE* node);
struct NODE* simplifare(struct NODE* node, struct NODE* root);
struct tokens_t* create_lec(struct CONVERSIONS* conversion);

struct NODE* GetC(struct CONVERSIONS* conversion, struct tokens_t* arr_token);
unsigned long long hash_func(int val, struct NODE* node);
void hash_all(struct NODE* val);
int print_node(struct NODE* node, FILE* file_l);
void create_latex_simplifare_diff(struct NODE* root);*/


#endif
