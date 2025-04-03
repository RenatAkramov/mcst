#include "bul.h"
struct CONVERSIONS* make_conversion()
{
    struct CONVERSIONS* conversion = (struct CONVERSIONS*) calloc(1, sizeof(struct CONVERSIONS));
    conversion->p = 0;
    conversion->amount_var = 0;

    FILE* file_in = fopen("primer.txt", "r");
    if (file_in == NULL)
    {
        perror("ERROR: in file_in");
        return NULL;
    }
    struct stat file_info = {0};
    char* file_name = "primer.txt";
        
    if (stat(file_name, &file_info) == -1)//Для нахождения длины строки в файле
    {
        fprintf(stderr, "ERROR: stat with %s\n", file_name);
        return NULL;
    }

    conversion->s = calloc((int) file_info.st_size + 1,sizeof(char));
    if (fgets(conversion->s, (int) file_info.st_size + 1, file_in) == NULL)
    {
        fprintf(stderr,"ERROR: in fgets\n");
        return NULL;
    }
    printf("%s\n", conversion->s);

    fclose(file_in);
    return conversion;
}

struct tokens_t* create_lec(struct CONVERSIONS* conversion)
{
    int len_buf = strlen(conversion->s); // Длина строчки
    struct tokens_t* arr_token = (struct tokens_t*) calloc(len_buf, sizeof(struct tokens_t));
    for (int i = 0; i < len_buf; i++)
    {
        arr_token[i].name = (char*) calloc(100, sizeof(char));
    }
    create_tokens(len_buf, conversion, arr_token);

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
        union values value = {-1};;
        if(conversion->s[i] == ' ')
        {
            i++;
        }
        else if(isdigit(conversion->s[i]))
        {
            arr_token[conversion->p].type = NUM;
            int j = 0;
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
            arr_token[conversion->p].type = OPER;
            value.oper_value = bracket_left;
            arr_token[conversion->p].name = "(";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        
        else if(conversion->s[i] == ')')
        {
            arr_token[conversion->p].type = OPER;
            value.oper_value = bracket_right;
            arr_token[conversion->p].value = value;
            arr_token[conversion->p].name = ")";
            conversion->p++;
            i++;
        }
       
        else if(conversion->s[i] == '$')
        {
            arr_token[conversion->p].type = OPER;
            value.oper_value = END;
            arr_token[conversion->p].name = "$";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == 'A' && conversion->s[i + 1] == 'N' && conversion->s[i + 2] == 'D')
        {
            arr_token[conversion->p].type = OPER;
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
            arr_token[conversion->p].type = OPER;
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
            arr_token[conversion->p].type = OPER;
            value.oper_value = OR;
            arr_token[conversion->p].name[0] = 'O';
            arr_token[conversion->p].name[1] = 'R';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 2;
        }
        else if(conversion->s[i] == 'X' && conversion->s[i + 1] == 'O' && conversion->s[i + 2] == 'R')
        {
            arr_token[conversion->p].type = OPER;
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
            arr_token[conversion->p].type = OPER;
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
            arr_token[conversion->p].type = OPER;
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
            arr_token[conversion->p].type = VAR;
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

