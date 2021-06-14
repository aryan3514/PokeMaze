#pragma once
#include "Unit.h"
#include <array>
#include <vector>
using namespace std;
class Matrix {

public:

    int width;
    int height;

    Unit** Area;


    Matrix();

    Matrix(int h, int w);

    Unit* GetUnitFromMatrix(int x, int y);

    vector<Unit*> GetNeighbours(Unit* un);

    Ash* FindAsh();

    bool IsSquirtleTaken();

    bool IsGastlyTaken();

    bool IsJigglyPuffTaken();

    bool IsZoroarkTaken();

};