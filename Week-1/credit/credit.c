#include <cs50.h>
#include <stdio.h>

/**
 * This program calculates the credit card validity based on the Luhn algorithm.
 *
 * @param card_number The credit card number provided by the user.
 * @return Returns true if the credit card number is valid according to the Luhn algorithm, otherwise false.
 *
 * The Luhn algorithm is used to validate various identification numbers, such as credit card numbers.
 * It works by summing the digits of the number, with every second digit from the right being doubled.
 * If the total modulo 10 is equal to 0, the number is considered valid.
 * 
 * For example, for the card number "4532015112830366", the program applies the algorithm
 * to check if the number is valid or not.
 */

int digit_length(long num)
{
    int length;

    length = 0;
    while (num != 0)
    {
        length++;
        num /= 10;
    }
    return (length);
}

long get_digits(long num, int n)
{
    while (num >= n * 10)
        num /= 10;
    return (num);
}

void card_type(long num)
{
    int length;
    long start_digit;

    length = digit_length(num);
    if (length < 13)
    {
        printf("INVALID\n");
        return;
    }
    if (length == 16)
    {
        start_digit = get_digits(num, 6);
        if (start_digit >= 51 && start_digit <= 55)
        {
            printf("MASTERCARD\n");
            return;
        }
    }
    if (length == 13 || length == 16)
    {
        start_digit = get_digits(num, 1);
        if (start_digit == 4)
        {
            printf("VISA\n");
            return;
        }
    }
    if (length == 15)
    {
        start_digit = get_digits(num, 4);
        if (start_digit == 34 || start_digit == 37)
        {
            printf("AMEX\n");
            return;
        }
    }
    printf("INVALID\n");
}

int calculate_checksum(long num)
{
    long n;
    int sum_even;
    int sum_odd;
    int total_sum;
    int digit;

    sum_even = 0;
    sum_odd = 0;
    n = num;
    while (n > 9)
    {
        digit = (n / 10) % 10;
        digit *= 2;
        if (digit > 9)
            digit = (digit / 10) + (digit % 10);
        sum_even += digit;
        n /= 100;
    }

    n = num;
    while (n > 0)
    {
        sum_odd += n % 10;
        n /= 100;
    }
    total_sum = sum_even + sum_odd;
    if (total_sum % 10 == 0)
        return (0);
    return (1);
}

int main(void)
{
    long num;

    do
    {
        num = get_long("Number: ");
    }
    while (num < 0);

    int credit = calculate_checksum(num);
    if (credit == 0)
        card_type(num);
    else
        printf("INVALID\n");
}
