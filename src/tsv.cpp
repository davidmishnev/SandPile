#include <iostream>
#include <filesystem>
#include <fstream>
#include <utility>

#include "tsv.h"


TsvReader::TsvReader(std::filesystem::path  path_to_file) : path_to_file(std::move(path_to_file)) {}

void TsvReader::OpenFile() {
    file_reader.open(this -> path_to_file, std::ifstream::binary);
    if (!file_reader.is_open()) {
        std::cerr << "Ошибка при открытии файла";
        exit(-1);
    }
}

void TsvReader::CloseFile() {
    file_reader.close();
}

void TsvReader::FindMatrixWidth() {
    OpenFile();
    char symbol;
    file_reader.get(symbol);
    while (symbol != '\n' && !file_reader.eof()) {
        if (symbol == '\t')
            width++;
        file_reader.get(symbol);
    }
    CloseFile();
}

void TsvReader::FindMatrixHeight() {
    OpenFile();
    char symbol;
    char prev_char = '\n';
    while (file_reader.get(symbol)) {
        if (symbol == '\n') {
            height++;
        }
        prev_char = symbol;
    }
    if (prev_char == '\n') {
        height--;
    }
    CloseFile();
}

SandyMatrix* TsvReader::Parse() {
    FindMatrixWidth();
    FindMatrixHeight();
    auto** file_matrix = new GrainOfSand*[height];
    for (int i = 0; i < height; i++) {
        file_matrix[i] = new GrainOfSand[width];
    }
    uint32_t number = 0;
    int cur_row = 0;
    int cur_col = 0;
    OpenFile();
    char symbol;
    file_reader.get(symbol);
    while (!file_reader.eof()) {
        if (std::isdigit(symbol)) {
            number = number * static_cast<uint32_t>(10) + static_cast<uint32_t>(symbol - '0');
        } else if (symbol == '\t' || symbol == '\n') {
            file_matrix[cur_row][cur_col].count = static_cast<uint32_t>(number);
            cur_col++;
            number = 0;
        }
        if (symbol == '\n') {
            cur_row++;
            cur_col = 0;
        }
        file_reader.get(symbol);
    }
    if (number) {
        file_matrix[cur_row][cur_col].count = static_cast<uint32_t>(number);
    }
    CloseFile();
    return new SandyMatrix(file_matrix, height, width);
}