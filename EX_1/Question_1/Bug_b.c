#include <stdio.h>

int main()
{

    int *ptr = NULL; // Declare a pointer but don't initialize it

    *ptr = 10; // This line triggers the error

    printf("This line won't be printed");

    return 0;
}