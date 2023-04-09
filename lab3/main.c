#include "functions.h"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Invalid input!\n");
        exit(1);
    }

    BITMAPFILEHEADER* fileHeader = NULL;
    BITMAPINFOHEADER* infoHeader = NULL;
    readFileHeader(argv[1]);
    readInfoHeader(argv[1]);
    readPixels(argv[1], *infoHeader);
    menu();
}