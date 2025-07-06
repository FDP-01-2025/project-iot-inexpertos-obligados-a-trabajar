#include "configuration.h"
#include "players.h"

Players players[4];
GameData game_data;
Difficulty difficulty;
ErrorType error_type;


void reset_game(std::vector<std::vector<int>> &bombXY){
    game_data.reset();
    difficulty.reset();
    error_type.reset();
    bombXY.clear();

    for (int i = 0; i < 4; i++)
    {
        players[i].points = 0; // Resets the points of the players
        players[i].is_alive = false; // Resets the state of the players
    }

}

