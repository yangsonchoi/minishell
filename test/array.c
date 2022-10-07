#include <stdio.h>

int main(void)
{
    int i = 0;
    char *test;

    &test[0] = "1234";

    while (i < 2)
    {
        printf("%s", &test[0][i]);
        i++;
    }
    return (0);
}