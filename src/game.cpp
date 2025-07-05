#include "game.h"

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