#include "game.h"
#include "players.h"
#include <algorithm>
#include <iostream>

void menu_difficulty(int dif)
{
    switch (dif)
    {
    case 1: // Easy
        difficulty.max_rows = 10;
        difficulty.max_columns = 10;
        difficulty.max_bombs = 30;
        difficulty.max_bullets = 10;
        difficulty.max_shields = 5;
        break;
    case 2: // Medium
        difficulty.max_rows = 20;
        difficulty.max_columns = 20;
        difficulty.max_bombs = 80;
        difficulty.max_bullets = 10;
        difficulty.max_shields = 5;
        break;
    case 3: // Hard
        difficulty.max_rows = 30;
        difficulty.max_columns = 30;
        difficulty.max_bombs = 100;
        difficulty.max_bullets = 10;
        difficulty.max_shields = 5;
        break;
    default: // Multiplayer
        break;
    }
}

void game_over_message() // Shows the error message
{
    if (error_type.bomb_explote) // Checks if the error type is bomb explosion
    {
        std::cout << "¡Has pisado una bomba!\n";
    }
    else if (error_type.repeat_coordinate) // Checks if the error type is repeat coordinate
    {
        std::cout << "¡Coordenada repetida! No es válido.\n";
    }
    else if (error_type.out_of_range) // Checks if the error type is out of range
    {
        std::cout << "¡Coordenada fuera del rango establecido!\n";
    }
    else if (error_type.data_type_invalid) // Checks if the error type is data type invalid
    {
        std::cout << "Dato inválido. Debe ingresar un número entero dentro del rango.\n";
    }
}

std::vector<std::vector<int>> random_coordinates(std::vector<std::vector<int>> &bombXY) // Generates random coordinates for the bombs
{
    int bombsTotal = difficulty.max_bombs;

    while (bombXY.size() < bombsTotal)
    {
        int bombX = rand() % difficulty.max_rows + 1; // Generates a random number between 1 and the maximum number of rows
        int bombY = rand() % difficulty.max_columns + 1; // Generates a random number between 1 and the maximum number of columns
        std::vector<int> candidate = {bombX, bombY};

        if (find(bombXY.begin(), bombXY.end(), candidate) == bombXY.end()) // Checks if the coordinate is already in the vector of bomb coordinates
        {
            bombXY.push_back(candidate); // Adds the coordinate to the vector of bomb coordinates
        }
    }
    return bombXY; // Returns the vector of bomb coordinates
}

bool prove_coordinates(const std::vector<int> &coordinate, const std::vector<std::vector<int>> &bombXY) // Checks if the coordinate is valid
{

    // Checks if the coordinate is out of range
    if ((coordinate[0] <= 0 || coordinate[0] > difficulty.max_columns) ||
        (coordinate[1] <= 0 || coordinate[1] > difficulty.max_rows))
    {
        error_type.out_of_range = true; // Sets the error type to out of range
        return true; // Returns true if the coordinate is out of range
    }

    // Checks if the coordinate is repeated
    if (find(game_data.repeat.begin(), game_data.repeat.end(), coordinate) != game_data.repeat.end())
    {
        error_type.repeat_coordinate = true; // Sets the error type to repeat coordinate
        return true; // Returns true if the coordinate is repeated
    }

    // Checks if the coordinate is a bomb
    if (find(bombXY.begin(), bombXY.end(), coordinate) != bombXY.end())
    {
        game_data.bomb_explote.push_back(coordinate); // Adds the coordinate to the vector of bomb coordinates
        error_type.bomb_explote = true; // Sets the error type to bomb explosion
        return true; // Returns true if the coordinate is a bomb
    }

    game_data.treasure_XY.push_back(coordinate); // Adds the coordinate to the vector of treasure coordinates    
    return false;
}

void reset_game_state(std::vector<std::vector<int>> &bombXY) // Resets the game state    
{
    game_data.reset(); // Resets the game state
    error_type.reset(); // Resets the error state
    bombXY.clear(); // Clears the vector of bomb coordinates
    for (int i = 0; i < 4; i++)
    {
        players[i].points = 0; // Resets the points of the players
        players[i].is_alive = false; // Resets the state of the players
    }
}