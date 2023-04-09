#ifndef LAB3_FUNCTIONS_H
#define LAB3_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)

typedef struct
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    uint32_t biSize;            // размер структуры
    int32_t biWidth;            // ширина изображения в пикселях
    int32_t biHeight;           // высота изображения в пикселях
    uint16_t biPlanes;          // количество цветовых плоскостей
    uint16_t biBitCount;        // бит на пиксель
    uint32_t biCompression;     // тип сжатия
    uint32_t biSizeImage;       // размер массива данных о пикселях
    int32_t biXPixelsPerMeter;    // количество пикселей на метр по горизонтали
    int32_t biYPixelsPerMeter;    // количество пикселей на метр по вертикали
    uint32_t biClrUsed;         // количество цветов в палитре
    uint32_t biClrImportant;    // количество значимых цветов в палитре
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct
{
    uint8_t BLUE;
    uint8_t GREEN;
    uint8_t RED;
} PIXEL;

BITMAPFILEHEADER* readFileHeader(char* file);

BITMAPINFOHEADER* readInfoHeader(char* file);

PIXEL** readPixels(char* file, BITMAPINFOHEADER infoHeader);

void displayMenu();

void menu();

#endif //LAB3_FUNCTIONS_H
