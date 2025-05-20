#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#pragma pack(push, 1)
typedef struct 
{
    unsigned char signature[2];
    unsigned int file_size;
    unsigned short reserved01;
    unsigned short reserved02;
    unsigned int offset_pixel_array;

    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bit_per_pixel;
    unsigned int compression;
    unsigned int pixel_data_size;
    unsigned int x_resolution;
    unsigned int y_resolution;
    unsigned int colors_palette;
    unsigned int imp_colors;
} BitmapHeader;
#pragma pack(pop)

typedef struct 
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;

#endif