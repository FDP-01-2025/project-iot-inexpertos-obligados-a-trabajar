#include "game.h"

void menu_difficulty(int dif)
{
    switch (dif)
    {
    case 1: // Fácil
        difficulty.maxRows = 10;
        difficulty.maxColumns = 10;
        difficulty.maxBombs = 30;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    case 2: // Medio
        difficulty.maxRows = 20;
        difficulty.maxColumns = 20;
        difficulty.maxBombs = 80;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    case 3: // Difícil
        difficulty.maxRows = 30;
        difficulty.maxColumns = 30;
        difficulty.maxBombs = 100;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    default: // Multijugador
        break;
    }
}

void game_over_message()
{
    if (error_type.bombExplote)
    {
        cout << "¡Has pisado una bomba!\n";
    }
    else if (error_type.repeatCoordinate)
    {
        cout << "¡Coordenada repetida! No es válido.\n";
    }
    else if (error_type.outOfRange)
    {
        cout << "¡Coordenada fuera del rango establecido!\n";
    }
    else if (error_type.dataTypeInvalid)
    {
        cout << "Dato inválido. Debe ingresar un número entero dentro del rango.\n";
    }
}

vector<vector<int>> random_coordinates(vector<vector<int>>& bombXY)
{
    int bombsTotal = difficulty.maxBombs;

    while (bombXY.size() < bombsTotal)
    {
        int bombX = rand() % difficulty.maxRows + 1;
        int bombY = rand() % difficulty.maxColumns + 1;
        vector<int> candidate = {bombX, bombY};

        if (find(bombXY.begin(), bombXY.end(), candidate) == bombXY.end())
        {
            bombXY.push_back(candidate);
        }
    }
    return bombXY;
}

bool prove_coordinates(const vector<int> &coordinate, const vector<vector<int>> &bombXY)
{

    // Verifica si está fuera de rango
    if ((coordinate[0] <= 0 || coordinate[0] > difficulty.maxColumns) ||
        (coordinate[1] <= 0 || coordinate[1] > difficulty.maxRows))
    {
        error_type.outOfRange = true;
        return true;
    }

    // Verifica si es coordenada repetida
    if (find(game_data.repeat.begin(), game_data.repeat.end(), coordinate) != game_data.repeat.end())
    {
        error_type.repeatCoordinate = true;
        return true;
    }

    // Verifica si es una bomba
    if (find(bombXY.begin(), bombXY.end(), coordinate) != bombXY.end())
    {
        game_data.bomb_explote.push_back(coordinate);
        error_type.bombExplote = true;
        return true;
    }

    game_data.treasureXY.push_back(coordinate);
    return false;
}