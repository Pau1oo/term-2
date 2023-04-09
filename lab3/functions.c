#include "functions.h"

void displayMenu()
{
    printf("[1] Negative\n");
    printf("[2] Black and white\n");
    printf("[3] Median filtering\n");
    printf("[4] Gamma-correction\n");
    printf("[0] Exit\n");
}

void menu()
{
    int choice;
    do {
        displayMenu();
        scanf_s("%d", &choice);
        switch(choice)
        {
            case 1:
                //
                break;
            case 2:
                //
                break;
            case 3:
                //
                break;
            case 4:
                //
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while(choice <= 4 && choice >= 0);
}

BITMAPFILEHEADER* readFileHeader(char* file)
{
    FILE* f = fopen(file, "rb");
    BITMAPFILEHEADER *fileHeader = NULL;
    fread(fileHeader, sizeof(*fileHeader), 1, f);
    fclose(f);
    return fileHeader;
}

BITMAPINFOHEADER* readInfoHeader(char* file)
{
    FILE* f = fopen(file, "rb");
    BITMAPINFOHEADER* infoHeader = NULL;
    fseek(f, 0, 14);
    fread(infoHeader, sizeof(*infoHeader), 1, f);
    fclose(f);
    return infoHeader;
}

PIXEL** readPixels(char* file, BITMAPINFOHEADER infoHeader)
{
    PIXEL** rgb = NULL;
    FILE* f = fopen(file, "rb");
    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;
    fseek(f, 0, 54);

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
    fclose(f);
    return rgb;
}