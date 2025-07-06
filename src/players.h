#ifndef PLAYERS_H
#define PLAYERS_H

#include <string>

struct Players
{
    std::string name;   // Nombre del jugador
    int points;    // Puntos acumulados
    int bullets;   // Balas disponibles
    int shields;   // Escudo disponible
    bool is_alive; // Indica si el jugador está vivo
};

extern Players players[4];

void player_configuration();
void player_action(int &turn, bool &lose);
void pistol_shot(int &turn, bool &lose);
void shield_protection(int &turn, bool &lose);

#endif