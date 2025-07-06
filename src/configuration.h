#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <vector>
#include <string>

struct Players
{
    std::string name;
    int points;
    int bullets;
    int shields;
    bool action_shoot;
    bool action_protect;
    bool excavate;
    bool is_alive;

    void actions_reset(){
        action_shoot = false;
        action_protect = false;
        excavate = false;
    }
};

extern Players players[4];

struct GameData
{
    int max_players;
    bool game_status = true;
    std::vector<std::vector<int>> bomb_explote;
    std::vector<std::vector<int>> repeat;
    std::vector<std::vector<int>> treasure_XY;

    void reset()
    {
        bomb_explote.clear();
        repeat.clear();
        treasure_XY.clear();
        max_players = 0;
        game_status = true;
    };
};

extern GameData game_data;

struct Difficulty
{
    int max_rows;
    int max_columns;
    int max_bombs;
    int max_bullets;
    int max_shields;

    void reset()
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
    bool bomb_explote;
    bool repeat_coordinate;
    bool out_of_range;
    bool data_type_invalid;

    void reset()
    {
        bomb_explote = false;
        repeat_coordinate = false;
        out_of_range = false;
        data_type_invalid = false;
    };
};

extern ErrorType error_type;

void reset_game(std::vector<std::vector<int>> &bombXY);

#endif
