#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "sandpile.h"

class TsvReader {
public:
    int32_t width = 1;
    int32_t height = 1;
    explicit TsvReader(std::filesystem::path  path_to_file);
    void OpenFile();
    void CloseFile();
    void FindMatrixWidth();
    void FindMatrixHeight();
    SandyMatrix* Parse();
private:
    std::filesystem::path path_to_file;
    std::ifstream file_reader;
};