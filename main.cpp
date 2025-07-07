#include "src/game.h"
#include "src/interface.h"
#include "src/players.h"
#include "src/configuration.h"
#include "src/save_load.h"
#include "src/sprites.h"
#include <iostream>

int main()
{
    int opcion;                           // Variable to store the option selected by the user
    std::vector<std::vector<int>> bombXY; // Vector of vectors to store the bomb coordinates
    bool game_on = true;
    int dif;

    std::cout << sprites.title;

    while (game_on)
    {
        std::cout << sprites.menu;
        std::cin >> opcion; // Reads the option selected by the user

        switch (opcion)
        {
        case 1:
            reset_game(bombXY);
            game_data.max_players = 1; // Sets the number of players to 1

            std::cout << sprites.dificulty;
            std::cin >> dif; // Reads the difficulty selected by the user

            menu_difficulty(dif);                // Sets the difficulty
            bombXY = random_coordinates(bombXY); // Generates random coordinates for the bombs
            player_configuration();              // Configures the players
            game(bombXY);
            break;
        case 2:
            reset_game(bombXY);

            std::cout << sprites.dificulty;
            std::cin >> dif;

            std::cout << "\n¿Con cuantos jugadores deseas jugar? (1-4): ";
            std::cin >> game_data.max_players;

            if (game_data.max_players < 1 || game_data.max_players > 4) // Checks if the number of players is valid
            {
                std::cout << "Numero de jugadores invalido. Debe ser entre 1 y 4.\n";
                continue;
            }

            menu_difficulty(dif);                // Sets the difficulty
            player_configuration();              // Configures the players
            bombXY = random_coordinates(bombXY); // Generates random coordinates for the bombs
            game(bombXY);
            break;
        case 3:
            reset_game(bombXY);
            load_game(bombXY);
            if (save_load.game_load)
            {
                game(bombXY);
                save_load.reset();
            }
            break;
        case 4:
            if (save_load.game_save)
            {
                save_game(bombXY);
                save_load.game_save = false;
            }
            else
            {
                std::cout << "¡No a iniciado una partida!";
            }
            break;
        case 5:
            std::cout << sprites.tutorial;
            break;
        case 6:
            std::cout << "¡Gracias por jugar! Hasta la próxima.\n"; // Shows the goodbye message
            game_on = false;
            break;
        default:
            std::cout << "\033[31mOpción no válida. Intenta de nuevo.\n\033[0m"; // Shows the invalid option message
            break;
        }
    }

    return 0;
}
