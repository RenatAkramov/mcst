#include "bul.h"

struct CONVERSIONS* make_conversion()
{
    struct CONVERSIONS* conversion = (struct CONVERSIONS*) calloc(1, sizeof(struct CONVERSIONS));
    conversion->p = 0;

    FILE* file_in = fopen("primer.txt", "r");
    if (file_in == NULL)
    {
        perror("Error in file_in");
        return NULL;
    }

    conversion->s = calloc(2000,sizeof(char));
    fgets(conversion->s, 2000, file_in);
    printf("%s\n", conversion->s);

    fclose(file_in);
    return conversion;
}

struct tokens_t* create_lec(struct CONVERSIONS* conversion)
{
    int len_buf = strlen(conversion->s); // Длина строчки
    //printf("len_buf: %d\n", len_buf);
    struct tokens_t* arr_token = (struct tokens_t*) calloc(len_buf, sizeof(struct tokens_t));
    for (int i = 0; i < len_buf; i++)
    {
        arr_token[i].name = (char*) calloc(100, sizeof(char));
    }
    create_tokens(len_buf, conversion, arr_token);
    //printf("LEC OK: %d\n", arr_token[1]. name);
    for (int i = 0; i < len_buf; i++)
    {
        printf("%s ", arr_token[i].name);
    }
    printf("\n");
    return arr_token;
}



int create_tokens(int len_buf, struct CONVERSIONS* conversion, struct tokens_t* arr_token)
{
    for (int i = 0; i < len_buf;)
    {
        union values value = {};
        //printf("i: %d p: %d\n", i, conversion->p);
        if(conversion->s[i] == ' ')
        {
            i++;
        }
        else if(isdigit(conversion->s[i]))
        {
            int ch = 0, j = 0;
            while (isdigit(conversion->s[i]))
            {
                assert(arr_token[conversion->p].name);
                arr_token[conversion->p].name[j] = conversion->s[i];
                i++;
                j++;
            }
            value.num_value = NUM;
            arr_token[conversion->p].value = value;
            conversion->p++;
        }
        else if(conversion->s[i] == '(')
        {
            value.oper_value = bracket_left;
            arr_token[conversion->p].name = "(";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        
        else if(conversion->s[i] == ')')
        {
            value.oper_value = bracket_right;
            arr_token[conversion->p].value = value;
            arr_token[conversion->p].name = ")";
            conversion->p++;
            i++;
        }
       
        else if(conversion->s[i] == '$')
        {
            value.oper_value = END;
            arr_token[conversion->p].name = "$";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == 'A' && conversion->s[i + 1] == 'N' && conversion->s[i + 2] == 'D')
        {
            value.oper_value = AND;
            arr_token[conversion->p].name[0] = 'A';
            arr_token[conversion->p].name[1] = 'N';
            arr_token[conversion->p].name[2] = 'D';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'N' && conversion->s[i + 1] == 'O' && conversion->s[i + 2] == 'T')
        {
            value.oper_value = NOT;
            arr_token[conversion->p].name[0] = 'N';
            arr_token[conversion->p].name[1] = 'O';
            arr_token[conversion->p].name[2] = 'T';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'O' && conversion->s[i + 1] == 'R')
        {
            value.oper_value = OR;
            arr_token[conversion->p].name[0] = 'O';
            arr_token[conversion->p].name[1] = 'R';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 2;
        }
        else if(conversion->s[i] == 'X' && conversion->s[i + 1] == 'O' && conversion->s[i + 2] == 'R')
        {
            value.oper_value = XOR;
            arr_token[conversion->p].name[0] = 'X';
            arr_token[conversion->p].name[1] = 'O';
            arr_token[conversion->p].name[2] = 'R';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'X' && conversion->s[i + 1] == 'N' && conversion->s[i + 2] == 'O' && conversion->s[i + 3] == 'R')
        {
            value.oper_value = XNOR;
            arr_token[conversion->p].name[0] = 'X';
            arr_token[conversion->p].name[1] = 'N';
            arr_token[conversion->p].name[2] = 'O';
            arr_token[conversion->p].name[3] = 'R';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'I' && conversion->s[i + 1] == 'M' && conversion->s[i + 2] == 'P')
        {
            value.oper_value = IMP;
            arr_token[conversion->p].name[0] = 'I';
            arr_token[conversion->p].name[1] = 'M';
            arr_token[conversion->p].name[2] = 'P';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if('A' <= conversion->s[i] && conversion->s[i] <= 'Z')
        {
            value.var_value = conversion->s[i];
            char* name_var = (char*) calloc(1, sizeof(char));
            name_var[0] = conversion->s[i];
            arr_token[conversion->p].name = name_var;
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        if(conversion->p - 2 >= 0)
        {
            printf("before: %s now: %s\n", arr_token[conversion->p - 2].name, arr_token[conversion->p - 1].name);
        }
    }
    printf("lec OK\n");
    conversion->p = 0;
    return 1;
}
