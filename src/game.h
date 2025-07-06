#ifndef GAME_H
#define GAME_H

#include <vector>

struct GameData
{
    int max_players; // Number of players
    bool game_status = true; // Game status
    std::vector<std::vector<int>> bomb_explote; // Coordenadas de bombas explotadas
    std::vector<std::vector<int>> repeat;       // Coordenadas repetidas
    std::vector<std::vector<int>> treasure_XY;   // Coordenadas de tesoros encontrados

    void reset()
    { // Resets the game state
        bomb_explote.clear(); // Clears the vector of bomb coordinates
        repeat.clear(); // Clears the vector of repeated coordinates
        treasure_XY.clear(); // Clears the vector of treasure coordinates
    }
};

extern GameData game_data;

struct Difficulty
{
    int max_rows;    // Maximum number of rows
    int max_columns; // Maximum number of columns
    int max_bombs;   // Maximum number of bombs
    int max_bullets; // Maximum number of bullets
    int max_shields; // Maximum number of shields
    void reset()
    { // Resets the values to the default values
        max_rows = 0;
        max_columns = 0;
        max_bombs = 0;
        max_bullets = 0;
        max_shields = 0;
    }
};

extern Difficulty difficulty;

struct ErrorType
{
    bool bomb_explote;      // Indicates if a bomb exploded
    bool repeat_coordinate; // Indicates if a coordinate was repeated
    bool out_of_range;       // Indicates if a coordinate is out of range
    bool data_type_invalid;  // Indicates if the data type is invalid

    void reset()
    { // Resets the game state
        bomb_explote = false;
        repeat_coordinate = false;
        out_of_range = false;
        data_type_invalid = false;
    };
};

extern ErrorType error_type;

void menu_difficulty(int dif); // Shows the menu difficulty
void game_over_message(); // Shows the game over message
std::vector<std::vector<int>> random_coordinates(std::vector<std::vector<int>>& bombXY); // Generates random coordinates for the bombs
bool prove_coordinates(const std::vector<int> &coordinate, const std::vector<std::vector<int>> &bombXY); // Checks if the coordinate is valid
void reset_game_state(std::vector<std::vector<int>> &bombXY); // Resets the game state

#endif