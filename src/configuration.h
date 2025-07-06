#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>
#include <string>

struct Players
{
    std::string name; // Name of the player
    int points; // Points of the player
    int bullets; // Bullets of the player
    int shields; // Shields of the player
    bool action_shoot; // Action to shoot
    bool action_protect; // Action to protect
    bool excavate; // Action to excavate
    bool is_alive; // State of the player

    void actions_reset() // Resets the actions of the player
    {
        action_shoot = false; 
        action_protect = false; 
        excavate = false; 
    }
};

extern Players players[4]; // Array of players

struct GameData
{
    int max_players; // Maximum number of players
    bool game_status = true; // State of the game
    std::vector<std::vector<int>> bomb_explote; // Vector of vectors to store the bomb coordinates
    std::vector<std::vector<int>> repeat; // Vector of vectors to store the repeat coordinates
    std::vector<std::vector<int>> treasure_XY; // Vector of vectors to store the treasure coordinates

    void reset() // Resets the game data
    {
        bomb_explote.clear(); // Clears the bomb coordinates
        repeat.clear(); // Clears the repeat coordinates
        treasure_XY.clear(); // Clears the treasure coordinates
        max_players = 0; // Resets the maximum number of players
        game_status = true; // Resets the state of the game
    };
};

extern GameData game_data; 

struct Difficulty
{
    int max_rows; // Maximum number of rows
    int max_columns; // Maximum number of columns
    int max_bombs; // Maximum number of bombs
    int max_bullets; // Maximum number of bullets
    int max_shields; // Maximum number of shields

    void reset() // Resets the difficulty
    {
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
    bool bomb_explote; // Error type for bomb explosion
    bool repeat_coordinate; // Error type for repeat coordinate
    bool out_of_range; // Error type for out of range
    bool data_type_invalid; // Error type for data type invalid

    void reset() // Resets the error type
    {
        bomb_explote = false;
        repeat_coordinate = false;
        out_of_range = false;
        data_type_invalid = false;
    };
};

extern ErrorType error_type;

void reset_game(std::vector<std::vector<int>> &bombXY); // Resets the game

#endif