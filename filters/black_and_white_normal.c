#include <stdio.h>
#include <stdlib.h>

#include "../data_types.h"

Pixel black_and_white(Pixel ***p, int width, int height)
{

    if (!p || !*p) return;

    Pixel gray_pixel;
    for (int y = height - 1; y >= 0; y--)
    {
        if (!(*p)[y]) continue;

        for (int x = 0; x < width; x++)
        {
            unsigned char gray_data = (unsigned char)(((*p)[y][x].blue + (*p)[y][x].green + (*p)[y][x].red)/3);
            Pixel gray_pixel = {gray_data, gray_data, gray_data};
        }
    }

    return gray_pixel;

}

