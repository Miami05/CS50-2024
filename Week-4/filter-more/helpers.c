#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 + 0.5);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
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
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
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
            int total_redSum = 0, total_greenSum = 0, total_blueSum = 0;
            float count = 0.00;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int currentRow = i + di;
                    int currentColumn = j + dj;
                    if (currentRow >= 0 && currentRow < height && currentColumn >= 0 &&
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
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
            int GxR = 0, GxG = 0, GxB = 0;
            int GyR = 0, GyG = 0, GyB = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int currentRow = di + i;
                    int currentColumn = dj + j;
                    if (currentRow >= 0 && currentRow < height && currentColumn >= 0 &&
                        currentColumn < width)
                    {
                        GxR = GxR + copy[currentRow][currentColumn].rgbtRed * Gx[di + 1][dj + 1];
                        GxG = GxG + copy[currentRow][currentColumn].rgbtGreen * Gx[di + 1][dj + 1];
                        GxB = GxB + copy[currentRow][currentColumn].rgbtBlue * Gx[di + 1][dj + 1];

                        GyR = GyR + copy[currentRow][currentColumn].rgbtRed * Gy[di + 1][dj + 1];
                        GyG = GyG + copy[currentRow][currentColumn].rgbtGreen * Gy[di + 1][dj + 1];
                        GyB = GyB + copy[currentRow][currentColumn].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }
            int Red = (int) (sqrt(GxR * GxR + GyR * GyR) + 0.5);
            int Green = (int) (sqrt(GxG * GxG + GyG * GyG) + 0.5);
            int Blue = (int) (sqrt(GxB * GxB + GyB * GyB) + 0.5);
            if (Red > 255)
                image[i][j].rgbtRed = 255;
            else
                image[i][j].rgbtRed = Red;
            if (Green > 255)
                image[i][j].rgbtGreen = 255;
            else
                image[i][j].rgbtGreen = Green;
            if (Blue > 255)
                image[i][j].rgbtBlue = 255;
            else
                image[i][j].rgbtBlue = Blue;
        }
    }
    return;
}
