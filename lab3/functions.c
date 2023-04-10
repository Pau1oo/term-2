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

void menu()
{
    while (1)
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

        if (choice == 0) exit(0);

        else if
                (choice == 1) printf("1");

        else if
                (choice == 2) printf("2");

        else if
                (choice == 3) printf("3");

        else if
                (choice == 4) printf("4");

        printf("\n");
    }
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