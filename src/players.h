#ifndef PLAYERS_H
#define PLAYERS_H

void player_configuration(); // Configures the players
// All the functions for the player actions are the next:
void pistol_shot(int &turn, bool &lose, bool &bomb_explote); // Pistol shot
void shield_action_protection(int &turn, bool &lose, bool &bomb_explote); // Shield action protection
void player_action(int &turn, bool &lose, bool &bomb_explote); // Player action

#endif