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

vector<Unit*> Matrix::GetNeighbours(Unit* un) {
    vector<Unit*> neburs;

    if (un == NULL) return neburs;
    int x = un->GetPos().x;
    int y = un->GetPos().y;

    if (y + 1 < height) {
        neburs.push_back(GetUnitFromMatrix(x, y + 1));
    }

    if (y - 1 >= 0) {
        neburs.push_back(GetUnitFromMatrix(x, y -1));
    }

    if (x + 1 < width) {
        neburs.push_back(GetUnitFromMatrix(x + 1, y));
    }

    if (x - 1 >= 0) {
        neburs.push_back(GetUnitFromMatrix(x-1, y));
    }

    return neburs;
}


Ash* Matrix::FindAsh() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (Area[j][i].GetAsh() != NULL) {
                return Area[j][i].GetAsh();
            }
        }
    }

    return NULL;
}


bool Matrix::IsSquirtleTaken() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (Area[j][i].GetSquirtle() != NULL) {
                return true;
            }
        }
    }

    return false;
}

bool Matrix::IsGastlyTaken() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (Area[j][i].GetGastly() != NULL) {
                return true;
            }
        }
    }

    return false;
}


bool Matrix::IsJigglyPuffTaken() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (Area[j][i].GetJigglyPuff() != NULL) {
                return true;
            }
        }
    }

    return false;
}

bool Matrix::IsZoroarkTaken() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (Area[j][i].GetZoroark() != NULL) {
                return true;
            }
        }
    }

    return false;
}


