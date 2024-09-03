#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * This program recovers JPEG images from a forensic image (a raw memory dump) by identifying JPEG file signatures.
 * It scans the input file block by block (512 bytes at a time), checking for JPEG signatures at the beginning of each block.
 * When a JPEG signature is found, it writes the data to a new JPEG file until another signature is found or the end of the file is reached.
 * This method demonstrates file recovery techniques by identifying and extracting data based on known file signatures.
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of ./recover\n");
        return (1);
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The card can not be opened\n");
        return (1);
    }
    uint8_t buffer[512];
    FILE *img = NULL;
    char filename[9];
    int file_number = 0;
    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
                fclose(img);
            sprintf(filename, "%03d.jpg", file_number++);
            img = fopen(filename, "w");
        }

        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img != NULL)
        fclose(img);
    fclose(card);
}
