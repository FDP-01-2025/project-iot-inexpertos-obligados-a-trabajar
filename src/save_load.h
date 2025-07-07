#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>
#include <string>
#include <fstream>
#include "configuration.h"

// Declaraciones de funciones
void save_players_data(std::ofstream &archivo); // Saves the players data
void load_players_data(std::ifstream &archivo); // Loads the players data
void save_game(const std::vector<std::vector<int>> &bombXY); // Saves the game
void load_game(std::vector<std::vector<int>> &bombXY); // Loads the game

#endif