#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Demo program 2: allocate memory and actually touch it all. */

int main (void) {
        int n = 0;
        char *p;

        while (1) {
                if ((p = malloc(1<<20)) == NULL) {
                        printf("malloc failure after %d MiB\n", n);
                        return 0;
                }
                memset (p, 0, (1<<20));
                printf ("got %d MiB\n", ++n);
        }
}

