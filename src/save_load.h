#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>
#include <string>
#include <fstream>

// Estructuras declaradas aquí para evitar dependencias circulares
struct Difficulty {
    int maxRows;
    int maxColumns;
    int maxBombs;
    int maxBullets;
    int maxShields;
    void reset();
};

struct GameData {
    int max_players;
    bool game_status;
    std::vector<std::vector<int>> bomb_explote;
    std::vector<std::vector<int>> repeat;
    std::vector<std::vector<int>> treasureXY;
    void reset();
};

struct Players {
    std::string name;
    int points;
    int bullets;
    int shields;
    bool action_shoot;
    bool action_protect;
    bool excavate;
    bool is_alive;
    void actions_reset();
};

// Declaraciones de funciones
void save_players_data(std::ofstream &archivo);
void load_players_data(std::ifstream &archivo);
void save_game(const std::vector<std::vector<int>> &bombXY);
void load_game(std::vector<std::vector<int>> &bombXY);

#endif