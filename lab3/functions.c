#include "functions.h"

void readHeader(char* file, BITMAPFILEHEADER* fileHeader, BITMAPINFOHEADER* infoHeader)
{
    FILE* f = fopen(file, "rb");
    fread(fileHeader, sizeof(*fileHeader), 1, f);
    fread(infoHeader, sizeof(*infoHeader), 1, f);
}

PIXEL** readPixels(FILE* f, BITMAPINFOHEADER infoHeader)
{
    PIXEL** rgb = NULL;
    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        for(int j = 0; i < infoHeader.biWidth; j++)
        {
            rgb[i][j].BLUE = getc(f);
            rgb[i][j].GREEN = getc(f);
            rgb[i][j].RED = getc(f);
            fseek(f, (long)padding, SEEK_CUR);
        }
    }
    return rgb;
}