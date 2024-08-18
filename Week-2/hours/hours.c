#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Program to calculate the total or average hours spent on CS50 problem sets over a given number of weeks.
 */

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

float calc_hours(int hours[], int weeks, char output)
{
    float sum = 0;
    int   i;
    for (i = 0; i < weeks; i++)
    {
        if (output == 'T')
            sum += hours[i];
        else if (output == 'A')
            sum += hours[i];
    }
    if (output == 'A')
        sum /= i;
    return (sum);
}
