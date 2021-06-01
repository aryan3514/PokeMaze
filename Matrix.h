#pragma once
#include "Unit.h"
#include <array>

class Matrix {

public:

    static int width;
    static int height;

    static Unit Area;

    Matrix(int h, int w);

    Unit* Matrix::GetUnitFromMatrix(int x, int y)

};