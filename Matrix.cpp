#include "Matrix.h"

Matrix::Matrix(int h, int w) {

    width = w;
    height = h;
    

    Area = new Unit* [w];
    for (int i = 0; i < w; ++i) {
        Area[i] = new Unit[h];
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Area[i][j].SetPos(i, j);
        }
    }
}

Unit* Matrix::GetUnitFromMatrix(int x, int y) {
    return Area[x][y];
}