#include "interface.h"
#include "game.h"
#include "players.h"
#include "configuration.h"
#include "sprites.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void print_board()
{
    bool bomb_coordinate, treasure_coordinate; // Variables to check if the coordinate is a bomb or a treasure

    std::cout << "\n=== GAME BOARD ===\n";
    // Print the column numbers
    std::cout << "   ";
    for (int column = 1; column <= difficulty.max_columns; column++)
    {
        if (column < 10)
            std::cout << " " << column << " ";
        else
            std::cout << column << " ";
    }
    std::cout << std::endl;

    for (int row = 1; row <= difficulty.max_rows; row++)
    {
        // Print the row number
        if (row < 10)
            std::cout << " " << row << " ";
        else
            std::cout << row << " ";

        for (int column = 1; column <= difficulty.max_columns; column++)
        {
            bomb_coordinate = false;
            treasure_coordinate = false;

            // Checks if the position contains an exploded bomb
            for (const std::vector<int> &bomb : game_data.bomb_explote)
            {
                if (bomb[0] == column && bomb[1] == row)
                {
                    bomb_coordinate = true;
                    break;
                }
            }

            // Checks if the position contains a treasure
            for (const std::vector<int> &treasure : game_data.treasure_XY)
            {
                if (treasure[0] == column && treasure[1] == row)
                {
                    treasure_coordinate = true;
                    break;
                }
            }

            // Prints the corresponding symbol
            if (bomb_coordinate)
            {
                std::cout << "\033[31m ! \033[0m";
            }
            else if (treasure_coordinate)
            {
                std::cout << "\033[92m $ \033[0m";
            }
            else
            {
               std::cout << "\033[33m # \033[0m";
            }
        }
        std::cout << std::endl;
    }
}

// Function for multiplayer mode
void game(std::vector<std::vector<int>> &bombXY)
{
    bool lose = false, bomb_explote = false;
    int positionX = 0, positionY = 0, retire = 0;
    std::vector<int> coordinate;

    // Show the initial board
    print_board();

    while (game_data.game_status)
    {
        for (int turn = 0; turn < game_data.max_players; ++turn)
        {
            if (players[turn].is_alive)
            {
                bomb_explote = false;
                error_type.reset(); // Reset error flags
                // Prints the turn of the player and the points
                std::cout << "\nTurno de " << players[turn].name << " (Puntos: " << players[turn].points << ")\n";
                std::cout << "Ingrese sus coordenadas (X Y): \n";
                std::cout << "X: ";
                std::cin >> positionX;
                std::cout << "Y: ";
                std::cin >> positionY;

                coordinate = {positionX, positionY};

                // Checks the coordinates
                lose = prove_coordinates(coordinate, bombXY);
                game_data.repeat.push_back(coordinate);

                player_action(turn, lose, bomb_explote); // Performs the action of the player

                if (!game_data.game_status)
                {
                    return;
                }

                if (lose)
                {
                    if (!players[turn].action_shoot && !players[turn].action_protect && error_type.bomb_explote)
                    {
                        game_over_message(); // Shows the game over message
                        players[turn].is_alive = false;
                        std::cout << players[turn].name << " pierde!\n"; // Shows the player who lost
                    }else if(error_type.out_of_range || error_type.repeat_coordinate){
                        game_over_message(); // Shows the game over message
                        players[turn].is_alive = false;
                        std::cout << players[turn].name << " pierde!\n"; // Shows the player who lost
                    }
                }
                else if (!bomb_explote && (players[turn].action_shoot || players[turn].action_protect || players[turn].excavate))
                {
                    // If the coordinate is valid
                    players[turn].points += 20;
                    std::cout<<sprites.treasure;
                    std::cout << "¡Tesoro encontrado! +20 puntos\n";
                }

                print_board();

                if (players[turn].points >= 60 && players[turn].is_alive)
                { // If the player has more than 60 points and is alive
                    std::cout << "¿Desea retirarse? (1=Sí, 0=No): ";
                    std::cin >> retire;
                    if (retire == 1)
                    { // If the player wants to retire
                        players[turn].is_alive = false;
                        players[turn].points += 40;
                    }
                }

                players[turn].actions_reset(); // Resets the actions of the player
            }
        }

        game_data.game_status = false; // Sets the game status to false
        for (int i = 0; i < game_data.max_players; i++)
        { // Checks if any player is still alive
            if (players[i].is_alive)
            {                                 // If the player is still alive
                game_data.game_status = true; // Sets the game status to true
                break;
            }
        }
    }

     int ganadorIndex = 0;
    int mayorPuntaje = players[0].points;
    for (int i = 1; i < game_data.max_players; i++) {
        if (players[i].points > mayorPuntaje) {
            mayorPuntaje = players[i].points;
            ganadorIndex = i;
        }
    }

    // shows the victory message
    victory(players[ganadorIndex].points, ganadorIndex);
}
