#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>

void save_game(const std::vector<std::vector<int>>& bombXY);
void load_game(std::vector<std::vector<int>>& bombXY);

#endif