#include "Matrix.h"

Matrix::Matrix() {
    Area = NULL;
    width = 0;
    height = 0;
}

Matrix::Matrix(int h, int w) {

    width = w;
    height = h;
    

    Area = new Unit* [h];
    for (int i = 0; i < h; ++i) {
        Area[i] = new Unit[w];
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            Area[i][j].SetPos(j,i);
        }
    }
}

Unit* Matrix::GetUnitFromMatrix(int x, int y) {
    return (&Area[y][x]);
}