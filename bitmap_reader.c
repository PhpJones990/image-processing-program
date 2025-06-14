#include <stdio.h>
#include <stdlib.h>

#include "data_types.h"
#include "filters/black_and_white_normal.h"
#include "filters/box_blur.h"

void cleanup_pixel(int height, Pixel ***data);
void filter_image(Pixel ***p, int width, int height, void (*filter)(Pixel***, int, int));

int main(int argc, char *argv[])
{
    // check arg
    if (argc != 3)
    {
        printf("Invalid Input\n");
        return -1;
    }

    // Open the file
    FILE *image_ptr = fopen(argv[1], "rb");
    if (!image_ptr)
    {
        printf("Failed to Open the Image!\n");
        perror("Failed to Open the Image!\n");
        return -1;
    }

    // Read the header
    BitmapHeader header;
    if (fread(&header, sizeof(BitmapHeader), 1, image_ptr) != 1)
    {
        printf("Failed to Read the Header!\n");
        perror("Failed to Read the Header!\n");
        fclose(image_ptr);
        return -1;
    }

    // Verify BMP file
    if (header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        printf("Invalid Input! Not a Bitmap file(BMP)!\n");
        perror("Invalid Input! Not a Bitmap file(BMP)!\n");
        fclose(image_ptr);
        return -1;
    }

    // Verify 24 bit uncompressed
    if (header.compression != 0)
    {
        printf("Not a 24 bitmap file!\n");
        perror("Not a 24 bitmap file!\n");
        fclose(image_ptr);
        return -1;
    }

    // Calculate Padding
    int padding = (4 - ((3*header.width) % 4)) % 4;

    // Allocate  memory for pixel data

    Pixel **pixels = (Pixel**)(malloc(sizeof(Pixel*) * header.height));
    if (!pixels)
    {
        printf("Failed to allocate memory of Pixel **pixels!\n");
        perror("Failed to allocate memory of Pixel **pixels!\n");
        fclose(image_ptr);
        return -1;
    }
    for (int i = 0; i < header.height; i++)
    {
        pixels[i] = (Pixel*)(malloc(sizeof(Pixel) * header.width));
        if (!pixels[i])
        {
            printf("Failed to allocate memory of pixel[i]!\n");
            perror("Failed to allocate memory of pixel[i]!\n");
            free(pixels);
            fclose(image_ptr);
            return -1;
        }
    }

    // Read raw pixel dat
    for (int y = header.height - 1; y >= 0; y--)
    {
        for (int x = 0; x < header.width; x++)
        {
            if (fread(&pixels[y][x], sizeof(Pixel), 1, image_ptr) != 1)
            {
                printf("Failed to Read Pixel data!\n");
                perror("Failed to Read Pixel data!\n");
                // Clean up
                cleanup_pixel(header.height, &pixels);
                fclose(image_ptr);
                return -2;
            }
        }
        // Skip padding
        fseek(image_ptr, padding, SEEK_CUR);
    }

    fclose(image_ptr);

    // Processing Part
    filter_image(&pixels, header.width, header.height, box_blur);

    // Write the output file
    FILE *output_image = fopen(argv[2], "wb");
    if (!output_image)
    {
        printf("Failed to open output image file!\n");
        perror("Failed to open output image file!\n");
        cleanup_pixel(header.height, &pixels);
        return -1;
    }

    // write header
    if (fwrite(&header, sizeof(BitmapHeader), 1, output_image) != 1)
    {
        printf("Failed to write header to output image file!\n");
        perror("Failed to write header to output image file!\n");
        cleanup_pixel(header.height, &pixels);
        fclose(output_image);
        return -1;
    }

    // write pixel data
    for (int y = header.height - 1; y >= 0; y--)
    {
        for (int x = 0; x < header.width; x++)
        {
            if (fwrite(&pixels[y][x], sizeof(Pixel), 1, output_image) != 1)
            {
                printf("Failed to write Pixel data to output image file!\n");
                perror("Failed to write Pixel data to output image file!\n");
                cleanup_pixel(header.height, &pixels);
                fclose(output_image);
                return -1;
            }
        }

        // write padding
        unsigned char padding_data = 0;
        for (int p = 0; p < padding; p++)
        {
            if (fwrite(&padding_data, 1, 1, output_image) != 1)
            {
                printf("Failed to write padding data!\n");
                perror("Failed to write padding data!\n");
                cleanup_pixel(header.height, &pixels);
                fclose(output_image);
                return -1;
            }
        }
    }

    // Cleanup
    cleanup_pixel(header.height, &pixels);
    fclose(output_image);
    printf("Image Processed Successfully!\n");

    printf("Fine!\n");
    return 0;
}

void cleanup_pixel(int height, Pixel ***data)
{
    for (int i = 0; i < height; i++) free((*data)[i]);
    free(*data);
    *data = NULL;
}

// This is the filter wrapper function
void filter_image(Pixel ***p, int width, int height, void (*filter)(Pixel***, int, int))
{
    filter(p, width, height);
}