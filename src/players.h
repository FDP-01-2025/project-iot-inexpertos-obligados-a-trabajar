#ifndef PLAYERS_H
#define PLAYERS_H

#include <string>

void player_configuration(); // Configures the players
// All the functions for the player actions are the next:
void player_action(int &turn, bool &lose, bool &bombo_explote);
void pistol_shot(int &turn, bool &lose, bool &bombo_explote);
void shield_action_protection(int &turn, bool &lose, bool &bombo_explote);

#endif