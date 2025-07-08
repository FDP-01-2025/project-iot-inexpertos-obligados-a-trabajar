#include "players.h"
#include "game.h"
#include "configuration.h"
#include "save_load.h"
#include "sprites.h"
#include <iostream>

void player_configuration() // Configures the players
{
    for (int i = 0; i < game_data.max_players; i++)
    {
        std::cout << "Nombre del jugador " << i + 1 << ": "; // Prints the name of the player
        std::cin >> players[i].name;
        players[i].points = 0;      // Sets the points to 0
        players[i].is_alive = true; // Sets the player to alive
        players[i].action_shoot = false;
        players[i].action_protect = false;
        players[i].bullets = difficulty.max_bullets; // Sets the number of bullets
        players[i].shields = difficulty.max_shields; // Sets the number of shields
    }
}

// Function for action_shooting with pistol
void pistol_shot(int &turn, bool &lose, bool &bomb_explote)
{
    if (players[turn].bullets == 0) // If the player has no bullets, he cannot shoot
    {
        std::cout<< sprites.pistol;
        std::cout << "\033[91m" << players[turn].name << " no tiene balas, no puede disparar\033[0m\n";

        return;
    }

    if (lose) // If the player loses, he gains 10 points and the bomb explodes
    {
        std::cout<< sprites.pistol;
        std::cout << players[turn].name << " has hecho explotar una bomba!, ha perdido\n";
        players[turn].is_alive = false;

        return;
    }
    else // If the player does not lose, he does not gain points
    {
        std::cout<< sprites.pistol;
        std::cout << players[turn].name << " haz encontrado un cofre a la distancia! +10 puntos extra\n";
        players[turn].points += 10;
    }

    players[turn].bullets--; // Decreases the number of bullets
    players[turn].action_shoot = true; // Sets the action to shoot
    lose = false; // Sets the lose to false
}

// Function for action_protecting with shield
void shield_action_protection(int &turn, bool &lose, bool &bomb_explote)
{
    if (players[turn].shields == 0) // If the player has no shields, he cannot protect himself
    {
        std::cout << "\033[91m" << players[turn].name << " no tiene escudos, no puede protegerse\033[0m\n";

        return;
    }

    if (lose) // If the player loses, he gains 10 points and the bomb explodes
    {
        std::cout<< sprites.shield;
        std::cout << players[turn].name << " se a protegido de una bomba! +10 puntos extra\n";
        players[turn].points += 10;
        bomb_explote = true;
    }
    else // If the player does not lose, he does not gain points
    {
        std::cout<< sprites.shield;
        std::cout << players[turn].name << " a gastado un escudo, no gana puntos extra\n";
    }

    players[turn].shields--; // Decreases the number of shields
    players[turn].action_protect = true; // Sets the action to protect
    lose = false; // Sets the lose to false
}

void player_action(int &turn, bool &lose, bool &bomb_explote) // Performs the action of the player
{
    std::cout << "\033[1;36m" << players[turn].name << " tiene:\n";
    std::cout << "\033[1;33m Balas: " << players[turn].bullets << "\n";
    std::cout << "\033[1;34m Escudos: " << players[turn].shields << "\n\033[0m\n";

    int action; // Action of the player
    std::cout << sprites.menu_action_player; // Prints the action of the player
    std::cin >> action;
    switch (action)
    {
    case 1: // Excavate
        std::cout << "Usted ha excavado... \n"; // Prints the action of the player
        players[turn].excavate = true; // Sets the action to excavate
        break;
    case 2: // action_protect
        shield_action_protection(turn, lose, bomb_explote); // Performs the action of the player
        break;
    case 3: // action_shoot with pistol
        pistol_shot(turn, lose, bomb_explote); // Performs the action of the player
        break;
    case 4: //Save
        save_load.game_save = true;
        game_data.game_status = false;    
    break;
    default:
        std::cout << "\033[91mAccion invalida, usted ha perdido\033[0m\n";
        players[turn].is_alive = false;
        break;
    }
}
