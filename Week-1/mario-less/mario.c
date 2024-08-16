#include <cs50.h>
#include <stdio.h>

/**
 * This program replicates the pyramid from the classic Mario game.
 * It prompts the user for the height of the pyramid, then prints a right-aligned pyramid of hashes (#) on the screen.
*/

int main(void)
{
    int num;

    do
    {
        num = get_int("Height: ");
    }
    while (num < 1);
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
        printf("\n");
    }
}
