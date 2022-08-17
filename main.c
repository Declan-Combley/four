#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Free {
    char *malloced[255];
    size_t index;
} Free;

char *alloc(Free *f, const char *value)
{
    char *s = malloc(sizeof(value));
    s = strcpy(s, value);
    f->malloced[f->index] = s;
    f->index++;

    return s;
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
    const char tens[9][8] = {"ten", "twenty", "thirty", "fourty", "fifty", "sixty", "sevennty", "eighty", "ninety"};

    if (sz < 9) {
        return alloc(f, ones[sz - 1]);
    }

    if (sz % 10 == 0) {
        size_t first = get_tens(sz);
        
        return alloc(f, tens[first - 1]);
    }

    return NULL;
}

void free_malloced(Free *f)
{
    for (size_t i = 0; i <= f->index; i++) {
        free(f->malloced[f->index]);
    }
}

int main(void)
{
    Free to_be_freed = {0};
    
    char *str = "threethree";
    size_t len = strlen(str);

    str = get_string_equivelent(len, &to_be_freed);
    printf("output: %s\n", str);

    free_malloced(&to_be_freed);
    
    return 0;
}

