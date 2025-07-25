#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "sandpile.h"
#include "ParseArguments.h"

#pragma pack(push, 1)


enum class Color {
    White,
    Black,
    Purple,
    Yellow,
    Green
};


struct BMPHeader {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int compression;
    unsigned int image_size;
    int x_pixels_per_meter;
    int y_pixels_per_meter;
    unsigned int colors_used;
    unsigned int colors_important;
};


struct RGBPalette {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved;
    void SetRGB(uint8_t R, uint8_t G, uint8_t B) {
        this -> red = R;
        this -> green = G;
        this -> blue = B;
        this -> reserved = 0;
    }

};

#pragma pack(pop)

class BMPWriter {
private:
    int out_path_size = 4096;
    char* output_path;
    Options options_;
    uint8_t row_addition{};
    BMPHeader header{};
    RGBPalette palette[16]{};

    void CreateBMPHeader(int32_t width, int32_t height);
    void CreateRGBPalette();
    void GenerateOutputPath(int32_t step);
    void SetPaletteColor(int32_t index, Color color);

public:
    explicit BMPWriter(Options user_arguments_);
    void Write(SandyMatrix* sandy_matrix);
    ~BMPWriter() {
        delete[] output_path;
    }
};