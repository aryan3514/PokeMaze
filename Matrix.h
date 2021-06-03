#pragma once
#include "Unit.h"
#include <array>

class Matrix {

public:

    int width;
    int height;

    Unit** Area;

    Matrix();

    Matrix(int h, int w);

    Unit* GetUnitFromMatrix(int x, int y);

};