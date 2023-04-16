#include "functions.h"

int main()
{
    char fileName[15];
    printf("Input the file name(.bmp):\n");
    gets(fileName);
    verify(fileName);
    BITMAPFILEHEADER* fileHeader = readFileHeader(fileName);
    BITMAPINFOHEADER* infoHeader = readInfoHeader(fileName);
    PIXEL** rgb = readPixels(fileName, *infoHeader);

    while(1)
    {
        int choice = menu();

        if (choice == 0) exit(0);

        else if
                (choice == 1) negative(rgb, *infoHeader, *fileHeader);

        else if
                (choice == 2) BnW(rgb, *infoHeader, *fileHeader);

        else if
                (choice == 3) medianFiltering(rgb, *infoHeader, *fileHeader);

        else if
                (choice == 4) gammaCorrection(rgb, *infoHeader, *fileHeader);

        printf("\n");
    }
}