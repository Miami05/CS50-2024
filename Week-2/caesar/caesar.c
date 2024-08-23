#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>



int get_key(string str)
{
    int i = 0;
    int temp;

    if (str[0] == '\0')
    {
        printf("Usage: ./caesar key\n");
        return (-1);
    }
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
        {
            printf("Usage: ./caesar key\n");
            return (-1);
        }
        i++;
    }
    temp = atoi(str);
    return (temp);
}

string encipher(string str, int key)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]) && isupper(str[i]))
           str[i] = (str[i] + key - 'A') % 26 + 'A';
        else if (isalpha(str[i]) && islower(str[i]))
           str[i] = (str[i] + key - 'a') % 26 + 'a';
    }
    return (str);
}

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int key = get_key(argv[1]);
        if (key == -1)
            return (1);
        string plaintext = get_string("plaintext:  ");
        string ciphertext = encipher(plaintext, key);
        printf("ciphertext: %s\n", ciphertext);
        return (0);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
}
