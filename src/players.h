#ifndef PLAYERS_H
#define PLAYERS_H

#include <string>

struct Players
{
    std::string name;   // Player name
    int points;    // Points accumulated
    int bullets;   // Available bullets
    int shields;   // Available shield
    bool is_alive; // Indicates if the player is alive
};

extern Players players[4];

void player_configuration(); // Configures the players
// All the functions for the player actions are the next:
void player_action(int &turn, bool &lose); 
void pistol_shot(int &turn, bool &lose); 
void shield_protection(int &turn, bool &lose); 

#endif