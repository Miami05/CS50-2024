#include <cs50.h>
#include <stdio.h>

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
