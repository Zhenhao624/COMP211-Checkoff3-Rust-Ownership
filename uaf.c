#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    *p = 42;
    free(p);

    // INTENTIONALLY UNSAFE: p points to memory that has been freed.
    // This access has undefined behavior in C.
    printf("%d\n", *p);
    return 0;
}
