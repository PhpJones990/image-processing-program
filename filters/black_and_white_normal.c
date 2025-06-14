#include <stdio.h>
#include <stdlib.h>

#include "../data_types.h"

void black_and_white(Pixel ***p, int width, int height)
{
    Pixel gray_pixel = {0, 0, 0};

    if (!p || !*p) return;

    for (int y = height - 1; y >= 0; y--)
    {
        if (!(*p)[y]) continue;

        for (int x = 0; x < width; x++)
        {
            unsigned char gray_data = (unsigned char)(((*p)[y][x].blue + (*p)[y][x].green + (*p)[y][x].red)/3);
            gray_pixel.blue = gray_data;
            gray_pixel.green = gray_data;
            gray_pixel.red = gray_data;
            (*p)[y][x] = gray_pixel;
        }
    }

    return;

}

