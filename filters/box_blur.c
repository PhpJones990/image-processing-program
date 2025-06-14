#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../data_types.h"

void box_blur(Pixel ***p, int width, int height)
{

    if (!p || !*p) return;

    for (int y = height - 1; y >= 0; y--)
    {
        if (!(*p)[y]) continue;

        for (int x = 0; x < width; x++)
        {
            float blue_sum = 0.0f;
            float green_sum = 0.0f;
            float red_sum = 0.0f;
            int count = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;

                    blue_sum += (*p)[ny][nx].blue;
                    green_sum += (*p)[ny][nx].green;
                    red_sum += (*p)[ny][nx].red;
                    
                    count++;
                }
            }

            
            (*p)[y][x].blue = (unsigned char)(roundf(blue_sum/count));
            (*p)[y][x].green = (unsigned char)(roundf(green_sum/count));
            (*p)[y][x].red = (unsigned char)(roundf(red_sum/count));
        }
    }

    return;
}