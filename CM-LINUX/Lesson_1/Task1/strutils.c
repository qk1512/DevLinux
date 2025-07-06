#include <ctype.h>
#include <string.h>
#include "strutils.h"

void str_reverse(char *str)
{
    if (!str)
        return;
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void str_trim(char *str)
{
    if (!str)
        return;

    // Trim leading whitespace
    int start = 0;
    while (isspace(str[start]))
        start++;

    // Trim trailing whitespace
    int end = strlen(str) - 1;
    while (end >= start && isspace(str[end]))
        end--;

    // Shift string and null terminate
    int i;
    for (i = 0; i <= end - start; i++)
    {
        str[i] = str[start + i];
    }
    str[i] = '\0';
}

int str_to_int(const char *str, int *out_num)
{
    if (!str || !out_num)
        return 0;

    // Skip leading whitespace
    while (isspace(*str))
        str++;

    // Handle empty string
    if (*str == '\0')
        return 0;

    int result = 0;
    int sign = 1;

    // Handle sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Convert digits
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    // Check if conversion was successful
    if (*str != '\0' && !isspace(*str))
        return 0;

    *out_num = result * sign;
    return 1;
}