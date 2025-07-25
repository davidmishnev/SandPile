#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <stack>


enum class ExpansionDirection;

struct GrainOfSand {
    int count = 0;
    int8_t add_count = 0;
    explicit GrainOfSand() = default;
    void concatenateCounts();
    uint8_t getColor() const;

};

class SandyMatrix {
private:

    void extendMatrix(ExpansionDirection overflow_direct);
    void mergeCounts() const;

public:
    GrainOfSand** matrix{};
    int height{};
    int width{};
    int step = 0;
    explicit SandyMatrix(GrainOfSand** matrix_, int height, int width);
    ~SandyMatrix() {
        for (int i = 0; i < height; ++i) {
            delete[] this->matrix[i];
        }
        delete matrix;
    }
    void printMatrix(const char* delimiter) const;
    bool calcStep();

};