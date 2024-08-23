#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

/**
 * This program calculates the score of words entered by two players based on the point values assigned to each letter in Scrabble.
 * Each player inputs a word, and the program computes the total score for each word by summing the points for each letter.
 * The program then compares the scores of the two words and declares the winner or indicates if there is a tie.
 */

int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int computer_score(string str)
{
    int temp = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (islower(str[i]))
        {
            temp += score[str[i] - 'a'];
        }
        if (isupper(str[i]))
            temp += score[str[i] - 'A'];
    }
    return (temp);
}

int main()
{
    string str1 = get_string("Player 1: ");
    string str2 = get_string("Player 2: ");

    int player1 = computer_score(str1);
    int player2 = computer_score(str2);
    if (player1 == player2)
        printf("Tie!\n");
    if (player1 < player2)
        printf("Player 2 wins\n");
    if (player1 > player2)
        printf("Player 1 wins\n");
}
