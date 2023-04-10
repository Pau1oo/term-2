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
    menu();
}