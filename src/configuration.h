#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>

struct Players
{
    std::string name;   // Player name
    int points;    // Points accumulated
    int bullets;   // Available bullets
    int shields;   // Available shield
    bool is_alive; // Indicates if the player is alive
};

extern Players players[4];

struct GameData
{
    int max_players;                            // Number of players
    bool game_status = true;                    // Game status
    std::vector<std::vector<int>> bomb_explote; // Coordenadas de bombas explotadas
    std::vector<std::vector<int>> repeat;       // Coordenadas repetidas
    std::vector<std::vector<int>> treasure_XY;  // Coordenadas de tesoros encontrados

    void reset(){
        bomb_explote.clear();
        repeat.clear();
        treasure_XY.clear();
        max_players = 0;
    };
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
    bool out_of_range;      // Indicates if a coordinate is out of range
    bool data_type_invalid; // Indicates if the data type is invalid

    void reset()
    { // Resets the game state
        bomb_explote = false;
        repeat_coordinate = false;
        out_of_range = false;
        data_type_invalid = false;
    };
};

extern ErrorType error_type;

void reset_game(std::vector<std::vector<int>> &bombXY);// Resets the game state

#endif