#ifndef GAME_H
#define GAME_H

#include <vector>
#include <algorithm>
#include <iostream>
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

struct ErrorType
{
    bool bombExplote;      // Indica si explotó una bomba
    bool repeatCoordinate; // Indica si se repitió coordenada
    bool outOfRange;       // Indica si coordenada está fuera de rango
    bool dataTypeInvalid;  // Indica si el tipo de dato es inválido

    void reset()
    { // Restablece el estado del juego
        bombExplote = false;
        repeatCoordinate = false;
        outOfRange = false;
        dataTypeInvalid = false;
    };
};

extern ErrorType error_type;

void menu_difficulty(int dif);
void game_over_message();
vector<vector<int>> random_coordinates(vector<vector<int>>& bombXY);

#endif