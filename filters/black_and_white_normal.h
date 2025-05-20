#include "../data_types.h"

Pixel black_and_white(Pixel p);
void filter_image(Pixel ***p, int width, int height, Pixel (*filter)(Pixel));