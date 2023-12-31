#include "helpers.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average intensity for grayscale using floating-point arithmetic
            float averageIntensity = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            // Round the average intensity to the nearest whole number without using math.h
            int roundedIntensity = (int) (averageIntensity + 0.5);

            // Change the pixel
            image[i][j].rgbtRed = (BYTE) roundedIntensity;   // Set red value
            image[i][j].rgbtGreen = (BYTE) roundedIntensity; // Set green value
            image[i][j].rgbtBlue = (BYTE) roundedIntensity;  // Set blue value
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia values for each channel with more precise rounding
            int spiared = (int) (0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue + 0.5);
            int spiagreen =
                (int) (0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue + 0.5);
            int spiablue = (int) (0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue + 0.5);

            // Ensure that the values are capped at 255
            image[i][j].rgbtRed = (BYTE) (spiared > 255 ? 255 : spiared);
            image[i][j].rgbtGreen = (BYTE) (spiagreen > 255 ? 255 : spiagreen);
            image[i][j].rgbtBlue = (BYTE) (spiablue > 255 ? 255 : spiablue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // Changed (width / 2) - 1 to width / 2
        {
            // Red reflection
            int r = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed; // Changed width - j to width - j - 1
            image[i][width - j - 1].rgbtRed = r;

            // Green reflection
            int g = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen; // Changed width - j to width - j - 1
            image[i][width - j - 1].rgbtGreen = g;

            // Blue reflection
            int b = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue; // Changed width - j to width - j - 1
            image[i][width - j - 1].rgbtBlue = b;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0;
            int count = 0;

            // Iterate through the surrounding pixels in a 3x3 grid
            for (int ni = i - 1; ni <= i + 1; ni++)
            {
                for (int nj = j - 1; nj <= j + 1; nj++)
                {
                    // Check if the surrounding pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        redSum += image[ni][nj].rgbtRed;
                        greenSum += image[ni][nj].rgbtGreen;
                        blueSum += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values with rounding
            temp[i][j].rgbtRed = (BYTE) ((float) redSum / count + 0.5);
            temp[i][j].rgbtGreen = (BYTE) ((float) greenSum / count + 0.5);
            temp[i][j].rgbtBlue = (BYTE) ((float) blueSum / count + 0.5);
        }
    }

    // Copy the blurred values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
