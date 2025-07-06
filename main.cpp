#include "src/game.h"
#include "src/interface.h"
#include "src/players.h"
#include "src/configuration.h"
#include <iostream>

int main()
{

    int opcion; // Variable to store the option selected by the user
    std::vector<std::vector<int>> bombXY;

    while (true)
    {

        // std::cout << sprites.menu;
        std::cin >> opcion; // Reads the option selected by the user

        if (opcion == 1)
        {
            reset_game(bombXY);
            game_data.max_players = 1; // Sets the number of players to 1

            int dif;
            std::cout << "\nSelecciona dificultad:\n"; 
            std::cout << "1. Fácil (10x10 - 30 bombas)\n";
            std::cout << "2. Medio (20x20 - 80 bombas)\n";
            std::cout << "3. Difícil (30x30 - 100 bombas)\n";
            std::cout << "Opción: ";
            std::cin >> dif; // Reads the difficulty selected by the user

            menu_difficulty(dif); // Sets the difficulty
            bombXY = random_coordinates(bombXY); // Generates random coordinates for the bombs
            player_configuration(); // Configures the players
            game(bombXY); // Plays the game
        }
        else if (opcion == 2)
        {
            reset_game(bombXY);

            int dif;
            std::cout << "\nSelecciona dificultad para Multijugador:\n";
            std::cout << "1. Fácil (10x10 - 30 bombas)\n";
            std::cout << "2. Medio (20x20 - 80 bombas)\n";
            std::cout << "3. Difícil (30x30 - 100 bombas)\n";
            std::cout << "Opción: ";
            std::cin >> dif;

            std::cout << "\n¿Con cuántos jugadores deseas jugar? (1-4): ";
            std::cin >> game_data.max_players;

            if (game_data.max_players < 1 || game_data.max_players > 4) // Checks if the number of players is valid
            {
                std::cout << "Número de jugadores inválido. Debe ser entre 1 y 4.\n";
                continue;
            }

            menu_difficulty(dif); // Sets the difficulty
            player_configuration(); // Configures the players
            bombXY = random_coordinates(bombXY); // Generates random coordinates for the bombs
            game(bombXY); // Plays the game
        }
        else if (opcion == 3)
        {
            // load_game(bombXY);
            print_board(); // Prints the board
        }
        else if (opcion == 4)
        {
            // save_game(bombXY);
        }
        else if (opcion == 5)
        {
            std::cout << "¡Gracias por jugar! Hasta la próxima.\n"; // Shows the goodbye message
            break;
        }
        else
        {
            std::cout << "Opción no válida. Intenta de nuevo.\n"; // Shows the invalid option message
        }
    }

    return 0;
}