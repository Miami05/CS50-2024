#include <cs50.h>
#include <stdio.h>

/**
 * This program prints a double-sided pyramid, similar to the pyramids in the Mario game.
 * The user is prompted to enter the height of the pyramid, and the program generates two pyramids of that height, separated by a gap.
 */

int main(void)
{
    int num;

    do
    {
        num = get_int("Height: ");
    }
    while (num < 1 || num > 8);

    for (int i = 1; i <= num; i++)
    {
        for (int j = 0; j < num - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
