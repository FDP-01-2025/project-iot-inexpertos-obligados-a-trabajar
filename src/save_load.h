#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>
#include <string>
#include <fstream>
#include "configuration.h"

// Declaraciones de funciones
void save_players_data(std::ofstream &archivo);
void load_players_data(std::ifstream &archivo);
void save_game(const std::vector<std::vector<int>> &bombXY);
void load_game(std::vector<std::vector<int>> &bombXY);

#endif
