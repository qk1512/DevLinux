#include <stdio.h>
#include <string.h>
#include "strutils.h"

int main()
{
    // Test str_reverse
    char str1[] = "Hello, World!";
    printf("Original: %s\n", str1);
    str_reverse(str1);
    printf("Reversed: %s\n", str1);

    // Test str_trim
    char str2[] = "   Spaces   ";
    printf("\nOriginal: '%s'\n", str2);
    str_trim(str2);
    printf("Trimmed: '%s'\n", str2);

    // Test str_to_int
    int num;
    const char *str3 = "  -123  ";
    if (str_to_int(str3, &num))
    {
        printf("\nString: '%s' -> Number: %d\n", str3, num);
    }
    else
    {
        printf("\nString: '%s' -> Conversion failed\n", str3);
    }

    return 0;
}