#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * This program converts a string representation of an integer to its numeric value using a recursive approach.
 * The function recursively processes each character of the string, accumulating the result to build the final integer value.
 * It handles positive and negative integers, ensuring correct conversion from string format to numeric format.
 * This method demonstrates the use of recursion to solve problems involving string manipulation and numerical conversion.
 */

int convert(string input);
int recursive_convet(string input, int result);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int recursive_convert(string input, int result)
{
    int sign = 1;
    int i = 0;

    while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
        i++;
    if (input[i] == '-' || input[i] == '+')
    {
        if (input[i] == '-')
            sign = -1;
        i++;
    }
    if (isdigit(input[i]))
    {
        result = result * 10 + (input[i] - '0');
        return (recursive_convert(input + i + 1, result));
    }
    return result * sign;
}

int convert(string input)
{
    return (recursive_convert(input, 0));
}
