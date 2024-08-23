#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * Count the number of alphabetic characters in the text.
 *
 * @param text The input string.
 * @return The number of alphabetic characters.
 */

int letter_count(string text)
{
    int len = strlen(text);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
            count++;
    }
    return (count);
}

int sentences_count(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
            count++;
    }
    return (count);
}

int words_count(string text)
{
    int count = 0;
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] != '\0' && !isspace(text[i]))
        {
            if (!words)
            {
                count++;
                words = 1;
            }
        }
        else
            words = 0;
    }
    return (count);
}

void print_grades(float count)
{
    if (count < 1)
        printf("Before Grade 1\n");
    else if (count == 1)
        printf("Grade 1\n");
    else if (count == 2)
        printf("Grade 2\n");
    else if (count == 3)
        printf("Grade 3\n");
    else if (count == 4)
        printf("Grade 4\n");
    else if (count == 5)
        printf("Grade 5\n");
    else if (count == 6)
        printf("Grade 6\n");
    else if (count == 7)
        printf("Grade 7\n");
    else if (count == 8)
        printf("Grade 8\n");
    else if (count == 9)
        printf("Grade 9\n");
    else if (count == 10)
        printf("Grade 10\n");
    else if (count == 11)
        printf("Grade 11\n");
    else if (count == 12)
        printf("Grade 12\n");
    else if (count == 13)
        printf("Grade 13\n");
    else if (count == 14)
        printf("Grade 14\n");
    else if (count == 15)
        printf("Grade 15\n");
    else if (count > 15)
        printf("Grade 16+\n");
}

int main(void)
{
    string text = get_string("Text: ");
    int letter = letter_count(text);
    int sentences = sentences_count(text);
    int words = words_count(text);
    float L = (float) letter / words * 100;
    float S = (float) sentences / words * 100;
    float count = 0.0588 * L - 0.296 * S - 15.8;
    int result = round(count);
    print_grades(result);
}
