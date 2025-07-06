#include "players.h" 
#include "game.h"
#include <iostream>

void player_configuration() // Configures the players
{
    for (int i = 0; i < game_data.max_players; i++)
    {
        std::cout << "Nombre del jugador " << i + 1 << ": "; // Prints the name of the player
        std::cin >> players[i].name;
        players[i].points = 0; // Sets the points to 0
        players[i].is_alive = true; // Sets the player to alive
        players[i].bullets = difficulty.max_bullets; // Sets the number of bullets
        players[i].shields = difficulty.max_shields; // Sets the number of shields
    }
}

void player_action(int &turn, bool &lose) // Performs the action of the player
{
    int action;
    std::cout << "¿Que desea hacer? (1=Excavar, 2=Protegerse, 3=Disparar con pistola): "; // Prints the action of the player
    std::cin >> action;
    switch (action)
    {
    case 1: // Excavate
        std::cout << "Usted ha excavado... \n";
        break;
    case 2: // Protect
        shield_protection(turn, lose);
        break;
    case 3: // Shoot with pistol
        pistol_shot(turn, lose);
        break;
    default:
        std::cout << "Acción inválida, intente nuevamente\n";
        break;
    }
}

// Function for shooting with pistol
void pistol_shot(int &turn, bool &lose)
{
    if (players[turn].bullets == 0)
    {
        std::cout << players[turn].name << " no tiene balas, no puede disparar\n";
        return;
    }
    else if (lose)
    {
        std::cout << players[turn].name << " a hecho explotar una bomba! +10 puntos\n";
    }
    else
    {
        std::cout << players[turn].name << " a desperdiciado una bala!, no gana puntos\n";
    }

    players[turn].bullets--;
    lose = false;
}

// Function for protecting with shield
void shield_protection(int &turn, bool &lose)
{
    if (players[turn].shields == 0)
    {
        std::cout << players[turn].name << " no tiene escudos, no puede protegerse\n";
        return;
    }
    else if (lose)
    {
        std::cout << players[turn].name << " se ha protegido de una bomba! +10 puntos\n";
        players[turn].shields--;
        lose = false;
    }
    else
    {
        std::cout << players[turn].name << " a gastado un escudo, no gana puntos\n";
        players[turn].shields--;
        lose = false;
    }
}