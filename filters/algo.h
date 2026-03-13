#ifndef ALGO_H 
#define ALGO_H 

#include "../data_types.h" 

void box_blur(Pixel ***p, int width, int height); 
void black_and_white(Pixel ***p, int width, int height); 
void invert_color(Pixel ***p, int width, int height); 

#endif 