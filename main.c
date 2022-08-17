#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Free {
    char *malloced[255];
    size_t index;
} Free;

char *get_string_equivelent(size_t sz, Free *f)
{
    const char ones[9][7] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    if (sz < 9) {
        char *s = malloc(sizeof(ones[sz - 1]));
        s = strcpy(s, ones[sz - 1]);
        f->malloced[f->index] = s;
        f->index++;
        return s;
    }

    return "amogus";
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
    
    char *str = "Mathematics";
    size_t len = strlen(str);

    str = get_string_equivelent(len, &to_be_freed);
    printf("output: %s\n", str);

    free_malloced(&to_be_freed);
    
    return 0;
}

