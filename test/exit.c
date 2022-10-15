#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
   int i = 0;
   while(i < 257)
    {
        printf("errno num: %d, msg: %s\n", i, strerror(i));
        i++;
    }
}