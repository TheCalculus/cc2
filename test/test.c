#include <stdio.h>

#define true 1

int main() {
    int integer = 0;
    printf("%d\n", integer);

    int i;
    for (i = 0; i < integer; i++)
        printf("iter %d\n", i);

    if (i <= integer) {
        integer |= 10;
        integer &= 2;
        integer ^= 1;
        integer = ~integer;
    } else {
        return -1;
    }

    while (true) {
        printf("%d, %s\n", true, true ? "true" : "false" );
        break;
    }

    return integer + 1;
}
