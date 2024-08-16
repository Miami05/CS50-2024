#include <cs50.h>
#include <stdio.h>

int calculate_quarter(int cents)
{
    int count = 0;

    while (cents >= 25)
    {
        count++;
        cents -= 25;
    }
    return (count);
}

int calculate_dimes(int cents)
{
    int count = 0;
    while (cents >= 10)
    {
        count++;
        cents -= 10;
    }
    return (count);
}

int calculate_nickel(int cents)
{
    int count = 0;
    while (cents >= 5)
    {
        count++;
        cents -= 5;
    }
    return (count);
}

int calculate_pennies(int cents)
{
    int count = 0;
    while (cents >= 1)
    {
        count++;
        cents -= 1;
    }
    return (count);
}

int main(void)
{
    int cents;

    do
    {
        cents = get_int("Change Owed: ");
    }
    while (cents < 0);

    int quarter = calculate_quarter(cents);
    cents = cents - (quarter * 25);

    int dime = calculate_dimes(cents);
    cents = cents - (dime * 10);

    int nickel = calculate_nickel(cents);
    cents = cents - (nickel * 5);

    int pennies = calculate_pennies(cents);
    cents = cents - (pennies * 1);

    int sum = quarter + dime + nickel + pennies;
    printf("%i\n", sum);
}
