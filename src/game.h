#ifndef GAME_H
#define GAME_H

#include <vector>
#include <algorithm>
using namespace std;

struct Difficulty
{
    int maxRows;    // Número máximo de filas
    int maxColumns; // Número máximo de columnas
    int maxBombs;   // Número máximo de bombas
    int maxBullets; // Número máximo de balas
    int maxShields; // Número máximo de escudos
    void reset()
    { // Restablece los valores predeterminados
        maxRows = 0;
        maxColumns = 0;
        maxBombs = 0;
        maxBullets = 0;
        maxShields = 0;
    }
};

extern Difficulty difficulty;

vector<vector<int>> random_coordinates(vector<vector<int>>& bombXY);

#endif