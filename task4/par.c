#include "par.h"

int main(int argc, char *argv[])
{
    struct Options opts = {0};
    int opt;
    struct option long_options[] = {{"elbrus", required_argument, 0, 'e'}, {0, 0, 0, 0}};

    opts.elbrus_values = calloc(argc ,sizeof(char*));
    opts.non_options   = calloc(argc, sizeof(char*));

    while (true) 
    {
        opt = getopt_long(argc, argv, "mcst", long_options, NULL);
        
        if (opt == -1) 
        {
            break;
        }
        
        switch (opt) 
        {
            case 'm': 
            {
                opts.m = 1; 
                break;
            }    

            case 'c': 
            {
                opts.c = 1; 
                break;
            }
            case 's': 
            {
                opts.s = 1; 
                break;
            }

            case 't': 
            {
                opts.t = 1; 
                break;
            }
            case 'e':
            {
                if (!is_valid_elbrus(optarg)) 
                {
                    fprintf(stderr, "Invalid elbrus value: %s\n", optarg);
                    error;
                }
                opts.elbrus_values[opts.elbrus_count++] = optarg;
                break;
            }    
            default:
            {
                fprintf(stderr, "Unknown option: %c\n", opt);
                error;
            }    
        }
    }    
    for (int i = optind; i < argc; i++) 
    {
        if (argv[i][0] != '-') 
        {
            opts.non_options[opts.non_count++] = argv[i];
        } 
        else 
        {
            fprintf(stderr, "Invalid option format: %s\n", argv[i]);
            error;
        }
    }

    printf("Options are correct:");
    if (opts.m == 1) 
    {
        printf(" m");
    }    
    if (opts.c == 1) 
    {
        printf(" c");
    }
    if (opts.s == 1) 
    {
        printf(" s");
    }
    if (opts.t == 1) 
    {
        printf(" t");
    }    
    
    for (int i = 0; i < opts.elbrus_count; i++) 
    {
        printf(" elbrus=%s", opts.elbrus_values[i]);
    }
    
    printf(", non-options:");
    for (int i = 0; i < opts.non_count; i++) 
    {
        printf(" %s", opts.non_options[i]);
    }
    printf("\n");
    
    free(opts.elbrus_values);
    free(opts.non_options);
    return 0;
    
}


int is_valid_elbrus(const char *value) 
{
    for (int i = 0; i < amount_elbrus_arg; i++) 
    {
        if (strcmp(value, valid_elbrus[i]) == 0) 
        {
            return 1;
        }    
    }
    return 0;
}