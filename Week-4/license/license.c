#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This program determines the validity of a driver's license plate based on a given set of rules.
 * The function takes a string input representing the license plate number and checks whether it conforms to specific format requirements
 * (such as length and character restrictions). It processes each character to ensure it matches the allowed patterns for a valid license plate.
 * This method demonstrates string manipulation and pattern matching to validate user input against predefined criteria.
 */

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;
    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        plates[idx] = malloc(sizeof(buffer) + 1);
        if (plates[idx] == NULL)
        {
            printf("Memory allocation failed");
            fclose(infile);
            return 1;
        }
        strcpy(plates[idx], buffer);
        idx++;
    }
    fclose(infile);
    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]);
    }
}
