#include <stdio.h>
#include <stdlib.h>

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

void cleanup_pixel(int width, Pixel ***data);

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
        perror("Failed to Open the Image!\n");
        return -1;
    }

    // Read the header
    BitmapHeader header;
    if (fread(&header, sizeof(BitmapHeader), 1, image_ptr) != 1)
    {
        perror("Failed to Read the Header!\n");
        fclose(image_ptr);
        return -1;
    }

    // Verify BMP file
    if (header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        perror("Invalid Input! Not a Bitmap file(BMP)!\n");
        fclose(image_ptr);
        return -1;
    }

    // Verify 24 bit uncompressed
    if (header.compression != 0)
    {
        perror("Not a 24 bitmap file!\n");
        fclose(image_ptr);
        return -1;
    }

    // Calculate Padding
    int padding = (4 - ((3*header.width) % 4)) % 4;

    // Allocate  memory for pixel data

    Pixel **pixels = (Pixel**)(malloc(sizeof(Pixel) * header.height));
    for (int i = 0; i < header.height; i++)
    {
        pixels[i] = (Pixel*)(malloc(sizeof(Pixel) * header.width));
    }

    // Read raw pixel dat
    for (int y = header.height - 1; y >= 0; y--)
    {
        for (int x = 0; x < header.width; x++)
        {
            if (fread(&pixels[y][x], sizeof(Pixel), 1, image_ptr) != 1)
            {
                perror("Failed to Read Pixel data!\n");
                // Clean up
                cleanup_pixel(header.width, &pixels);
                fclose(image_ptr);
                return -2;
            }
        }
        // Skip padding
        fseek(image_ptr, padding, SEEK_CUR);
    }

    fclose(image_ptr);
        

    // Processing Part

    // Write the output file
    FILE *output_image = fopen(argv[2], "wb");
    if (!output_image)
    {
        perror("Failed to open output image file!\n");
        cleanup_pixel(header.width, &pixels);
        return -1;
    }

    // write header
    if (fwrite(&header, sizeof(BitmapHeader), 1, output_image) != 1)
    {
        perror("Failed to write header to output image file!\n");
        cleanup_pixel(header.width, &pixels);
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
                perror("Failed to write Pixel data to output image file!\n");
                cleanup_pixel(header.width, &pixels);
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
                perror("Failed to write padding data!\n");
                cleanup_pixel(header.width, &pixels);
                fclose(output_image);
                return -1;
            }
        }
    }

    // Cleanup
    cleanup_pixel(header.width, &pixels);
    fclose(output_image);
    printf("Image Processed Successfully!\n");

    printf("Fine!\n");
    return 0;
}

void cleanup_pixel(int width, Pixel ***data)
{
    for (int i = 0; i < width; i++) free(*data[i]);
    free(*data);
    *data = NULL;
}