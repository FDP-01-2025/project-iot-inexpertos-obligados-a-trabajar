#include "players.h"
#include "game.h"
#include "configuration.h"
#include <iostream>

void player_configuration() // Configures the players
{
    for (int i = 0; i < game_data.max_players; i++)
    {
        std::cout << "Nombre del jugador " << i + 1 << ": "; // Prints the name of the player
        std::cin >> players[i].name;
        players[i].points = 0;                       // Sets the points to 0
        players[i].is_alive = true;                  // Sets the player to alive
        players[i].action_shoot = false;
        players[i].action_protect = false;
        players[i].bullets = difficulty.max_bullets; // Sets the number of bullets
        players[i].shields = difficulty.max_shields; // Sets the number of shields
    }
}

// Function for action_shooting with pistol
void pistol_shot(int &turn, bool &lose, bool &bomb_explote)
{
    if (players[turn].bullets == 0)
    {
        std::cout << players[turn].name << " no tiene balas, no puede disparar\n";
        return;
    }

    if (lose)
    {
        std::cout << players[turn].name << " a hecho explotar una bomba! +10 puntos extra\n";
        players[turn].points += 10;
        bomb_explote = true;
    }
    else
    {
        std::cout << players[turn].name << " a desperdiciado una bala!, no gana puntos extra\n";
    }

    players[turn].bullets--;
    players[turn].action_shoot = true;
    lose = false;
}

// Function for action_protecting with shield
void shield_action_protection(int &turn, bool &lose, bool &bomb_explote)
{
    if (players[turn].shields == 0)
    {
        std::cout << players[turn].name << " no tiene escudos, no puede protegerse\n";
        return;
    }

    if (lose)
    {
        std::cout << players[turn].name << " se a protegido de una bomba! +10 puntos extra\n";
        players[turn].points += 10;
        bomb_explote = true;
    }
    else
    {   
        std::cout << players[turn].name << " a gastado un escudo, no gana puntos extra\n";
    }

    players[turn].shields--;
    players[turn].action_protect = true;
    lose = false;
}

void player_action(int &turn, bool &lose, bool &bomb_explote) // Performs the action of the player
{
    int action;
    std::cout << "¿Que desea hacer? (1=Excavar, 2=Protegerse, 3=Disparar con pistola): "; // Prints the action of the player
    std::cin >> action;
    switch (action)
    {
    case 1: // Excavate
        std::cout << "Usted ha excavado... \n";
        players[turn].excavate = true;
        break;
    case 2: // action_protect
        shield_action_protection(turn, lose, bomb_explote);
        break;
    case 3: // action_shoot with pistol
        pistol_shot(turn, lose, bomb_explote);
        break;
    default:
        std::cout << "Acción inválida, intente nuevamente\n";
        break;
    }
}