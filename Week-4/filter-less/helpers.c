#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ave =
                (int) ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 +
                       0.5);
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed =
                (int) ((0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue) + 0.5);
            int sepiaGreen =
                (int) ((0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue) + 0.5);
            int sepiaBlue =
                (int) ((0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue) + 0.5);

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total_redSum = 0;
            int total_greenSum = 0;
            int total_blueSum = 0;
            float count = 0.00;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int currentRow = i + di;
                    int currentColumn = j + dj;
                    if (currentRow >= 0 && currentColumn >= 0 && currentRow < height &&
                        currentColumn < width)
                    {
                        total_redSum += copy[currentRow][currentColumn].rgbtRed;
                        total_greenSum += copy[currentRow][currentColumn].rgbtGreen;
                        total_blueSum += copy[currentRow][currentColumn].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = (int) ((total_redSum / count) + 0.5);
            image[i][j].rgbtGreen = (int) ((total_greenSum / count) + 0.5);
            image[i][j].rgbtBlue = (int) ((total_blueSum / count) + 0.5);
        }
    }
    return;
}
