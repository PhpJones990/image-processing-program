#include <stdio.h>
#include <stdlib.h>

#include "../data_types.h"

Pixel black_and_white(Pixel p)
{
    unsigned char gray_data = (unsigned char)((p.blue + p.green + p.red)/3);
    Pixel gray_pixel = {gray_data, gray_data, gray_data};
    return gray_pixel;

}

void filter_image(Pixel ***p, int width, int height, Pixel (*filter)(Pixel))
{
    if (!p || !*p) return;

    for (int y = height - 1; y >= 0; y--)
    {
        if (!(*p)[y]) continue;

        for (int x = 0; x < width; x++)
        {
            (*p)[y][x] = filter((*p)[y][x]);
        }
    }
}
    