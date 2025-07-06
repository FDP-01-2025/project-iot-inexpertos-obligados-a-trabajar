#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include <vector>
#include <string>

// Función para guardar partida
void save_game(const std::vector<std::vector<int>> &bombXY);

// Función para cargar partida
void load_game(std::vector<std::vector<int>> &bombXY);

#endif