#include "configuration.h"
#include "players.h"

Players players[4]; // Array of players
GameData game_data; // Game data
Difficulty difficulty; // Difficulty
ErrorType error_type; // Error type
SaveLoad save_load;

void reset_game(std::vector<std::vector<int>> &bombXY)
{
    save_load.reset();
    game_data.reset(); // Resets the game data
    difficulty.reset(); // Resets the difficulty
    error_type.reset(); // Resets the error type
    bombXY.clear(); // Clears the bombXY

    for (int i = 0; i < 4; i++)
    {
        players[i].points = 0;       // Resets the points of the players
        players[i].is_alive = false; // Resets the state of the players
    }
}