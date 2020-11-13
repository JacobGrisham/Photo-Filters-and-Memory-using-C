#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over the image (array (height) of array (width))
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Create variable to obtain individual RGB values
            RGBTRIPLE original = image[j][i];
            // Create variable to store average value
            // Calculate average of red, green, and blue to ensure each pixel retains same general brightness and darkness
            int average = round((original.rgbtBlue + original.rgbtGreen + original.rgbtRed) / 3.0);
            // Change each pixel to the same rounded average value
            image[j][i].rgbtBlue = average;
            image[j][i].rgbtGreen = average;
            image[j][i].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over the image (array (height) of array (width))
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Obtain RGB value
            RGBTRIPLE original = image[j][i];
            int originalRed = original.rgbtRed;
            int originalGreen = original.rgbtGreen;
            int originalBlue = original.rgbtBlue;
            // Calculate sepia values and round any decimals to nearest integer
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            // If above 255, set to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            // For each pixel change the red, green, and blue to the new corresponding sepia value
            image[j][i].rgbtBlue = sepiaBlue;
            image[j][i].rgbtGreen = sepiaGreen;
            image[j][i].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new bitmap variable to avoid altering original image
    RGBTRIPLE copy[height][width];

    // Iterate backwards over the image
    for (int j = height - 1; j >= 0; j--)
    {
        // Create empty variable to store original position
        int original = 0;
        // Iterate backwards over the image
        for (int i = width - 1; i >= 0; i--, original++)
        {
            copy[j][original] = image[j][i];
        }
    }

    // Iterate over the image (array (height) of array (width))
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Copy new bitmap into original bitmap
            image[j][i] = copy[j][i];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create new bitmap variable to avoid altering original image
    RGBTRIPLE copy[height][width];


    // Iterate over the image (array (height) of array (width))
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Create variable to keep track of cells referenced for averaging later on
            int num = 0;
            // Create variables that act as the radius from the cell in question
            int Y[] = {j - 1, j, j + 1};
            int X[] = {i - 1, i, i + 1};
            // Create variables to set inital sum for each individual RGB value
            float total_blue = 0;
            float total_green = 0;
            float total_red = 0;

            // Begin process for blurring using the scope of a 3x3 box
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    // Create 3x3 box radius over the cell in question
                    int col = Y[y];
                    int row = X[x];

                    // Validate the bounds (such as edges and corners)
                    if (col >= 0 && col < width && row >= 0 && row < height)
                    {
                        // Create variable to obtain individual, original RGB values
                        RGBTRIPLE value = image[row][col];

                        // Sum up all the RGB values within the 3x3 box for each color
                        total_blue += value.rgbtBlue;
                        total_green += value.rgbtGreen;
                        total_red += value.rgbtRed;

                        // Keep track of number of cells referenced for averaging later on
                        num++;
                    }
                }
            }
            // Finally, blur the image by setting the RGB values of the copied image to the average of the surrounding values
            copy[i][j].rgbtBlue = round(total_blue / num);
            copy[i][j].rgbtGreen = round(total_green / num);
            copy[i][j].rgbtRed = round(total_red / num);
        }
    }

    // Lastly, transfer all this work into the original image
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            // Copy new bitmap into original bitmap
            image[j][i] = copy[j][i];
        }
    }
    return;
}
