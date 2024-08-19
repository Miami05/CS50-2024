// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'e')
            str[i] = '3';
        if (str[i] == 'a')
            str[i] = '6';
        if (str[i] == 'i')
            str[i] = '1';
        if (str[i] == 'o')
            str[i] = '0';
    }
    return (str);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of ./no-vowels\n");
    }
    else
    {
        char *str = replace(argv[1]);
        printf("%s\n", str);
    }
    return (1);
}
