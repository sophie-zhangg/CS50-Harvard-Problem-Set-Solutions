#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize and declare average value of the three channels

    int avrg_val = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avrg_val = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float)3);
            image[i][j].rgbtRed = avrg_val;
            image[i][j].rgbtGreen = avrg_val;
            image[i][j].rgbtBlue = avrg_val;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create temporary pixel
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        //search through half of the image
        for (int j = 0; j < width / 2; j++)
        {
            //save each pixel in temp and then save new pixel at the place of the previous pixel
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            //save the temp pixel at the new place
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float average = 0;
    //save the original image in a copy
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    //blur all the pixel (sans the border)
    for (int i = 1; i < height - 1 ; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = round((original[i - 1][j - 1].rgbtRed + original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j - 1].rgbtRed + original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / (float)9);
            image[i][j].rgbtGreen = round((original[i - 1][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / (float)9);
            image[i][j].rgbtBlue = round((original[i - 1][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / (float)9);
        }
    }
    //blur the border
    //blurring the corners
    image[0][0].rgbtRed = round((original[0][0].rgbtRed + original[1][0].rgbtRed + original[0][1].rgbtRed + original[1][1].rgbtRed) / (float)4);
    image[0][0].rgbtGreen = round((original[0][0].rgbtGreen + original[1][0].rgbtGreen + original[0][1].rgbtGreen + original[1][1].rgbtGreen) / (float)4);
    image[0][0].rgbtBlue = round((original[0][0].rgbtBlue + original[1][0].rgbtBlue + original[0][1].rgbtBlue + original[1][1].rgbtBlue) / (float)4);

    image[0][width - 1].rgbtRed = round((original[0][width - 2].rgbtRed + original[0][width - 1].rgbtRed + original[1][width - 2].rgbtRed + original[1][width - 1].rgbtRed) / (float)4);
    image[0][width - 1].rgbtGreen = round((original[0][width - 2].rgbtGreen + original[0][width - 1].rgbtGreen + original[1][width - 2].rgbtGreen + original[1][width - 1].rgbtGreen) / (float)4);
    image[0][width - 1].rgbtBlue = round((original[0][width - 2].rgbtBlue + original[0][width - 1].rgbtBlue + original[1][width - 2].rgbtBlue + original[1][width - 1].rgbtBlue) / (float)4);

    image[height - 1][0].rgbtRed = round((original[height - 2][0].rgbtRed + original[height - 2][1].rgbtRed + original[height - 1][0].rgbtRed + original[height - 1][1].rgbtRed) / (float)4);
    image[height - 1][0].rgbtGreen = round((original[height - 2][0].rgbtGreen + original[height - 2][1].rgbtGreen + original[height - 1][0].rgbtGreen + original[height - 1][1].rgbtGreen) / (float)4);
    image[height - 1][0].rgbtBlue = round((original[height - 2][0].rgbtBlue + original[height - 2][1].rgbtBlue + original[height - 1][0].rgbtBlue + original[height - 1][1].rgbtBlue) / (float)4);

    image[height - 1][width - 1].rgbtRed = round((original[height - 2][width - 2].rgbtRed + original[height - 2][width - 1].rgbtRed + original[height - 1][width - 2].rgbtRed + original[height - 1][width - 1].rgbtRed) / (float)4);
    image[height - 1][width - 1].rgbtGreen = round((original[height - 2][width - 2].rgbtGreen + original[height - 2][width - 1].rgbtGreen + original[height - 1][width - 2].rgbtGreen + original[height - 1][width - 1].rgbtGreen) / (float)4);
    image[height - 1][width - 1].rgbtBlue = round((original[height - 2][width - 2].rgbtBlue + original[height - 2][width - 1].rgbtBlue + original[height - 1][width - 2].rgbtBlue + original[height - 1][width - 1].rgbtBlue) / (float)4);

    //finish up the sides of the picture array (not corners or insides)
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtRed = round((original[i - 1][0].rgbtRed + original[i - 1][1].rgbtRed + original[i][0].rgbtRed + original[i][1].rgbtRed + original[i + 1][0].rgbtRed + original[i + 1][1].rgbtRed) / (float)6);
        image[i][0].rgbtGreen = round((original[i - 1][0].rgbtGreen + original[i - 1][1].rgbtGreen + original[i][0].rgbtGreen + original[i][1].rgbtGreen + original[i + 1][0].rgbtGreen + original[i + 1][1].rgbtGreen) / (float)6);
        image[i][0].rgbtBlue = round((original[i - 1][0].rgbtBlue + original[i - 1][1].rgbtBlue + original[i][0].rgbtBlue + original[i][1].rgbtBlue + original[i + 1][0].rgbtBlue + original[i + 1][1].rgbtBlue) / (float)6);

        image[i][width - 1].rgbtRed = round((original[i - 1][width - 2].rgbtRed + original[i - 1][width - 1].rgbtRed + original[i][width - 2].rgbtRed + original[i][width - 1].rgbtRed + original[i + 1][width - 2].rgbtRed + original[i + 1][width - 1].rgbtRed) / (float)6);
        image[i][width - 1].rgbtGreen = round((original[i - 1][width - 2].rgbtGreen + original[i - 1][width - 1].rgbtGreen + original[i][width - 2].rgbtGreen + original[i][width - 1].rgbtGreen + original[i + 1][width - 2].rgbtGreen + original[i + 1][width - 1].rgbtGreen) / (float)6);
        image[i][width - 1].rgbtBlue = round((original[i - 1][width - 2].rgbtBlue + original[i - 1][width - 1].rgbtBlue + original[i][width - 2].rgbtBlue + original[i][width - 1].rgbtBlue + original[i + 1][width - 2].rgbtBlue + original[i + 1][width - 1].rgbtBlue) / (float)6);
    }
    for (int j = 1; j < width - 1; j++)
    {
        image[0][j].rgbtRed = round((original[0][j - 1].rgbtRed + original[1][j - 1].rgbtRed + original[0][j].rgbtRed + original[1][j].rgbtRed + original[0][j + 1].rgbtRed + original[1][j + 1].rgbtRed) / (float)6);
        image[0][j].rgbtGreen = round((original[0][j - 1].rgbtGreen + original[1][j - 1].rgbtGreen + original[0][j].rgbtGreen + original[1][j].rgbtGreen + original[0][j + 1].rgbtGreen + original[1][j + 1].rgbtGreen) / (float)6);
        image[0][j].rgbtBlue = round((original[0][j - 1].rgbtBlue + original[1][j - 1].rgbtBlue + original[0][j].rgbtBlue + original[1][j].rgbtBlue + original[0][j + 1].rgbtBlue + original[1][j + 1].rgbtBlue) / (float)6);

        image[height - 1][j].rgbtRed = round((original[height - 2][j - 1].rgbtRed + original[height - 1][j - 1].rgbtRed + original[height - 2][j].rgbtRed + original[height - 1][j].rgbtRed + original[height - 2][j + 1].rgbtRed + original[width - 1][j + 1].rgbtRed) / (float)6);
        image[height - 1][j].rgbtGreen = round((original[height - 2][j - 1].rgbtGreen + original[height - 1][j - 1].rgbtGreen + original[height - 2][j].rgbtGreen + original[height - 1][j].rgbtGreen + original[height - 2][j + 1].rgbtGreen + original[width - 1][j + 1].rgbtGreen) / (float)6);
        image[height - 1][j].rgbtBlue = round((original[height - 2][j - 1].rgbtBlue + original[height - 1][j - 1].rgbtBlue + original[height - 2][j].rgbtBlue + original[height - 1][j].rgbtBlue + original[height - 2][j + 1].rgbtBlue + original[width - 1][j + 1].rgbtBlue) / (float)6);
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the original
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }

    //kernels
    int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    //save the sums of the channel values
    float Gx_sum[3];
    float Gy_sum[3];

    int red_val;
    int green_val;
    int blue_val;

    //search through all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //clear the sum of the channel values
            for (int c = 0; c < 3; c++)
            {
                Gx_sum[c] = 0;
                Gy_sum[c] = 0;

            }
            //search through the 3x3 box around the pixel
            for (int c = i - 1; c < i + 2; c++)
            {
                for (int a = j - 1; a < j + 2; a++)
                {
                    //check if the pixel is outside of the image
                    if (c >= 0 && a >= 0 && c < height && a < width)
                    {
                        //add to the sum
                        Gx_sum[0] += original[c][a].rgbtRed * Gx[c - i + 1][a - j + 1];
                        Gx_sum[1] += original[c][a].rgbtGreen * Gx[c - i + 1][a - j + 1];
                        Gx_sum[2] += original[c][a].rgbtBlue * Gx[c - i + 1][a - j + 1];

                        Gy_sum[0] += original[c][a].rgbtRed * Gy[c - i + 1][a - j + 1];
                        Gy_sum[1] += original[c][a].rgbtGreen * Gy[c - i + 1][a - j + 1];
                        Gy_sum[2] += original[c][a].rgbtBlue * Gy[c - i + 1][a - j + 1];
                    }
                }
            }
            //apply the Sobel operator algorithm
            red_val = round(sqrt((double)(pow(Gx_sum[0], 2) + pow(Gy_sum[0], 2))));
            green_val = round(sqrt((double)(pow(Gx_sum[1], 2) + pow(Gy_sum[1], 2))));
            blue_val = round(sqrt((double)(pow(Gx_sum[2], 2) + pow(Gy_sum[2], 2))));

            //check if the RGB value is less than 255, set the value to 255 if greater than
            if (red_val > 255)
            {
                red_val = 255;
            }
            if (green_val > 255)
            {
                green_val = 255;
            }
            if (blue_val > 255)
            {
                blue_val = 255;
            }

            //set the image of the edited values
            image[i][j].rgbtRed = red_val;
            image[i][j].rgbtGreen = green_val;
            image[i][j].rgbtBlue = blue_val;
        }
    }
    return;
}
