#include "photograph.h"
#include <stdio.h>

#define WIDTH 50
void p01() {
    int i,j,k;
    for(i=0; i<WIDTH; i++)
        putchar('*');
    putchar('\n');
    for(i=0; i<WIDTH/5; i++) {
        j=WIDTH/2-i;
        for(j; j>=0; j--)
            putchar(' ');
        for(k=0; k<=i; k++)
            putchar('*');
        putchar('\n');
    }
    for(i=0; i<WIDTH; i++)
        putchar('*');
}

