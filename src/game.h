#ifndef GAME_H
#define GAME_H

#include <vector>

void menu_difficulty(int dif); // Shows the menu difficulty
void game_over_message(); // Shows the game over message
std::vector<std::vector<int>> random_coordinates(std::vector<std::vector<int>>& bombXY); // Generates random coordinates for the bombs
bool prove_coordinates(const std::vector<int> &coordinate, const std::vector<std::vector<int>> &bombXY); // Checks if the coordinate is valid
bool victory(int points, int playerIndex); // Shows the victory screen

#endif
