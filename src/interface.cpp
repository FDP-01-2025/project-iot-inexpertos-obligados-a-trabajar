#include "interface.h"
#include "game.h"
#include "players.h"
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
                std::cout << " ! ";
            }
            else if (treasure_coordinate)
            {
                std::cout << " $ ";
            }
            else
            {
                std::cout << " # ";
            }
        }
        std::cout << std::endl;
    }
}

// Function for multiplayer mode
void game(std::vector<std::vector<int>> &bombXY)
{
    bool lose = false;
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

                player_action(turn, lose); // Performs the action of the player

                if (lose)
                {                        // If the player loses
                    game_over_message(); // Shows the game over message
                    if (error_type.bomb_explote)
                    { // If the player loses
                        players[turn].is_alive = false;
                        std::cout << players[turn].name << " lost!\n"; // Shows the player who lost
                    }
                }
                else
                { // If the coordinate is valid
                    players[turn].points += 20;
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
                    }
                }
            }
        }

        game_data.game_status = false;
        for (int i = 0; i < game_data.max_players; i++)
        { // Checks if any player is still alive
            if (players[i].is_alive)
            { // If the player is still alive
                game_data.game_status = true;
                break;
            }
        }
    }

    std::cout << "\n=== GAME OVER ===\n";
    for (int i = 0; i < game_data.max_players; i++)
    { // Prints the points of each player
        std::cout << players[i].name << ": " << players[i].points << " puntos\n";
    }
}