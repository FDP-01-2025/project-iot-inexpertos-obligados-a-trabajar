#ifndef PLAYERS_H
#define PLAYERS_H

#include <string>

void player_configuration(); // Configures the players
// All the functions for the player actions are the next:
void player_action(int &turn, bool &lose); 
void pistol_shot(int &turn, bool &lose); 
void shield_protection(int &turn, bool &lose); 

#endif