#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct Free {
    char *malloced[255];
    size_t index;
} Free;

void free_malloced(Free *f)
{
    for (size_t i = 0; i <= f->index; i++) {
        free(f->malloced[f->index]);
    }
}

char *alloc(Free *f, const char *value)
{
    char *s = malloc(sizeof(value));
    s = strcpy(s, value);
    f->malloced[f->index] = s;
    f->index++;

    return s;
}

size_t get_end(size_t sz)
{
    return sz % 10;
}

size_t get_tens(size_t sz)
{
    size_t first = sz;
        
    while(first >= 10 ) {
            first = first / 10;
    }

    return first;
}

char *get_string_equivelent(size_t sz, Free *f)
{
    if (sz >= 100) {
        fprintf(stderr, "error: %zu is invalid: string must be greater than 0 and less than 100\n", sz);
        exit(1);
    }
    
    const char ones[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const char teens[9][9] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char tens[9][8] = {"ten", "twenty", "thirty", "fourty", "fifty", "sixty", "sevennty", "eighty", "ninety"};

    if (sz <= 9) {
        return alloc(f, ones[sz - 1]);
    }

    if (sz % 10 == 0) {
        size_t first = get_tens(sz);
        
        return alloc(f, tens[first - 1]);
    }

    if (sz > 10 && sz < 20) {
        return alloc(f, teens[sz - 11]);
    }

    char *first = alloc(f, tens[get_tens(sz) - 1]);
    char *second = alloc(f, ones[get_end(sz) - 1]);

    strcat(first, " ");
    strcat(first, second);
    
    char *s = malloc(sizeof(sizeof(tens[get_tens(sz) - 1]) + sizeof(ones[get_end(sz) - 1])));

    strcpy(s, first);
    f->malloced[f->index] = s;
    f->index++;

    return s;
}

size_t len(char *s)
{
    return strlen(s);
}

int main(int argc, char **argv)
{
    assert(argv != NULL);

    if (argc != 2) {
        fprintf(stderr, "error: invalid input: expected a string\n");
        fprintf(stderr, "eg     ./four 'text'\n");
        exit(1);
    }

    for (size_t i = 0; i <= len(argv[1]); i++) {
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            fprintf(stderr, "error: %s is invalid: input must not contain a number\n", argv[1]);
            exit(1);
        } 
    }
    
    Free to_be_freed = {0};
    
    char *str = argv[1];
    size_t length = len(str);

    printf("           %s\n", str);

    while (1) {
        str = get_string_equivelent(length, &to_be_freed);
        length = len(str);
        printf("%11s | %zu digits\n", str, length);

        if (len(str) == 4) {
            str = get_string_equivelent(length, &to_be_freed);
            printf("%11s | 4 digits\n", str);
            printf("         ...| 4 digits\n");
            printf("          ..| 4 digits\n");
            printf("           .| 4 digits\n");
            break;
        }
    }
    
    free_malloced(&to_be_freed);
    
    return 0;
}

