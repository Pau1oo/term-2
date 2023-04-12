#include "functions.h"

void verify(char* fileName)
{
    const char* point = strrchr(fileName, '.');
    if(strcmp(point, ".bmp") != 0)
    {
        printf("This is not a BMP file\n");
        getchar();
        exit(0);
    }
}

void displayMenu()
{
    printf("[1] Negative\n");
    printf("[2] Black and white\n");
    printf("[3] Median filtering\n");
    printf("[4] Gamma-correction\n");
    printf("[0] Exit\n");
}

int menu()
{
    int choice;
    system("cls");
    displayMenu();
    while (!scanf_s("%d", &choice) || choice > 4 || choice < 0 || getchar() != '\n')
    {
        system("cls");
        printf("Invalid choice!\n");
        printf("Choose again!\n");
        printf("\n");
        displayMenu();
        rewind(stdin);
    }
    return choice;
}

BITMAPFILEHEADER* readFileHeader(char* fileName)
{
    FILE* f = fopen(fileName, "rb");
    if(f == NULL)
    {
        printf("Error opening file\n");
        fclose(f);
        return NULL;
    }

    BITMAPFILEHEADER *fileHeader = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, f);
    fclose(f);
    return fileHeader;
}

BITMAPINFOHEADER* readInfoHeader(char* fileName)
{
    FILE* f = fopen(fileName, "rb");
    if(f == NULL)
    {
        printf("Error opening file\n");
        fclose(f);
        return NULL;
    }

    BITMAPINFOHEADER* infoHeader = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    fseek(f, 14, SEEK_SET);
    fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, f);
    fclose(f);
    return infoHeader;
}

PIXEL** readPixels(char* fileName, BITMAPINFOHEADER infoHeader)
{
    PIXEL** rgb = malloc(sizeof(PIXEL*) * infoHeader.biHeight);

    FILE* f = fopen(fileName, "rb");
    if(f == NULL)
    {
        printf("Error opening file\n");
        fclose(f);
        return NULL;
    }

    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;
    fseek(f, 54, SEEK_SET);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        rgb[i] = malloc(sizeof(PIXEL) * infoHeader.biWidth);
        for(int j = 0; j < infoHeader.biWidth; j++)
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

void negative(PIXEL** rgb, BITMAPINFOHEADER infoHeader, BITMAPFILEHEADER fileHeader)
{
    PIXEL** newRGB = malloc(sizeof(PIXEL*) * infoHeader.biHeight);
    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;
    unsigned long long paddingSize = padding * sizeof(unsigned char);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        newRGB[i] = malloc(sizeof(PIXEL) * infoHeader.biWidth);
        for(int j = 0; j < infoHeader.biWidth; j++)
        {
            newRGB[i][j].BLUE = 255 - rgb[i][j].BLUE;
            newRGB[i][j].GREEN = 255 - rgb[i][j].GREEN;
            newRGB[i][j].RED = 255 - rgb[i][j].RED;
        }
    }

    FILE* outputFile = fopen("negative.bmp", "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, outputFile);
    fwrite(&infoHeader, sizeof(infoHeader), 1, outputFile);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        fwrite(newRGB[i], sizeof(PIXEL), infoHeader.biWidth, outputFile);
        fwrite(0, paddingSize, 1, outputFile);
    }

    fclose(outputFile);
}

void BnW(PIXEL** rgb, BITMAPINFOHEADER infoHeader, BITMAPFILEHEADER fileHeader)
{
    PIXEL** newRGB = malloc(sizeof(PIXEL*) * infoHeader.biHeight);
    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;
    unsigned long long paddingSize = padding * sizeof(unsigned char);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        newRGB[i] = malloc(sizeof(PIXEL) * infoHeader.biWidth);
        for(int j = 0; j < infoHeader.biWidth; j++)
        {
            int average = (rgb[i][j].BLUE + rgb[i][j].GREEN + rgb[i][j].RED) / 3;
            newRGB[i][j].BLUE = average;
            newRGB[i][j].GREEN = average;
            newRGB[i][j].RED = average;
        }
    }

    FILE* outputFile = fopen("black&white.bmp", "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, outputFile);
    fwrite(&infoHeader, sizeof(infoHeader), 1, outputFile);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        fwrite(newRGB[i], sizeof(PIXEL), infoHeader.biWidth, outputFile);
        fwrite(0, paddingSize, 1, outputFile);
    }

    fclose(outputFile);
}

void gammaCorrection(PIXEL** rgb, BITMAPINFOHEADER infoHeader, BITMAPFILEHEADER fileHeader)
{
    PIXEL** newRGB = malloc(sizeof(PIXEL*) * infoHeader.biHeight);
    unsigned long long padding = (4 - (infoHeader.biWidth * sizeof(PIXEL)) % 4) % 4;
    unsigned long long paddingSize = padding * sizeof(unsigned char);
    float gamma;
    printf("Input the gamma coefficient:\n");
    scanf_s("%f", &gamma);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        newRGB[i] = malloc(sizeof(PIXEL) * infoHeader.biWidth);
        for(int j = 0; j < infoHeader.biWidth; j++)
        {
            float blueValue = (float)rgb[i][j].BLUE / 255;
            float greenValue = (float)rgb[i][j].GREEN / 255;
            float redValue = (float)rgb[i][j].RED / 255;
            newRGB[i][j].BLUE = (uint8_t)(powf(blueValue, gamma) * 255);
            newRGB[i][j].GREEN = (uint8_t)(powf(greenValue, gamma) * 255);
            newRGB[i][j].RED = (uint8_t)(powf(redValue, gamma) * 255);
        }
    }

    FILE* outputFile = fopen("gamma.bmp", "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, outputFile);
    fwrite(&infoHeader, sizeof(infoHeader), 1, outputFile);

    for(int i = 0; i < infoHeader.biHeight; i++)
    {
        fwrite(newRGB[i], sizeof(PIXEL), infoHeader.biWidth, outputFile);
        fwrite(0, paddingSize, 1, outputFile);
    }

    fclose(outputFile);
}