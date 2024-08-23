#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * This program implements a substitution cipher for text encryption.
 * It maps each letter in the input text to a different letter based on a provided key.
 * The key is a string of 26 unique alphabetical characters that represents the substitution mapping.
 * The user inputs the key and the plaintext to be encrypted.
 * The program then outputs the ciphertext, which is the result of applying the substitution cipher to the input text.
 * 
 * The substitution cipher replaces each letter in the plaintext with a corresponding letter from the key.
 * For instance, if the key is "ZEBRASCDFGHIJKLMNOPQRSTUVWXYA", then 'A' is substituted with 'Z', 'B' with 'E', etc.
 * 
 * The program handles both uppercase and lowercase letters, preserving their cases in the ciphertext.
 * Non-alphabetic characters (such as spaces and punctuation) are left unchanged in the output.
 * The program also checks for the validity of the key, ensuring it contains all 26 unique alphabetical characters.
 */

bool is_valid(string str)
{
    char c;
    bool seen[26] = {false};
    int index = 0;

    if (strlen(str) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return (false);
    }
    for (int i = 0; i < 26; i++)
    {
        c = str[i];
        if (!isalpha(c))
        {
            printf("Key must only contain alphabetic character\n");
            return (false);
        }
        c = toupper(c);
        index = c - 'A';
        if (seen[index])
        {
            printf("Key must not contain repeated characters\n");
            return (false);
        }
        seen[index] = true;
    }
    return (true);
}

void encipher(string str, string key)
{
    char c = '\0';
    printf("ciphertext: ");
    for (int i = 0; str[i] != '\0'; i++)
    {
        c = str[i];
        if (islower(str[i]))
            str[i] = tolower(key[c - 'a']);
        else if (isupper(str[i]))
            str[i] = toupper(key[c - 'A']);
    }
    printf("%s\n", str);
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    string key = argv[1];
    if (!is_valid(key))
        return (1);
    string plaintext = get_string("plaintext:  ");
    encipher(plaintext, key);
}
