#include "interface.h"
#include "game.h"
#include "players.h"
#include <iostream>

void print_board()
{
    bool bomb_coordinate, treasure_coordinate;

    std::cout << "\n=== TABLERO DE JUEGO ===\n";
    // Imprimir números de columnas
    std::cout << "   ";
    for (int col = 1; col <= difficulty.maxColumns; col++)
    {
        if (col < 10)
            std::cout << " " << col << " ";
        else
            std::cout << col << " ";
    }
    std::cout << std::endl;

    for (int row = 1; row <= difficulty.maxRows; row++)
    {
        // Imprimir número de fila
        if (row < 10)
            std::cout << " " << row << " ";
        else
            std::cout << row << " ";

        for (int column = 1; column <= difficulty.maxColumns; column++)
        {
            bomb_coordinate = false;
            treasure_coordinate = false;

            // Verifica si la posición contiene una bomba explotada
            for (const std::vector<int> &bomb : game_data.bomb_explote)
            {
                if (bomb[0] == column && bomb[1] == row)
                {
                    bomb_coordinate = true;
                    break;
                }
            }

            // Verifica si la posición contiene un tesoro
            for (const std::vector<int> &treasure : game_data.treasureXY)
            {
                if (treasure[0] == column && treasure[1] == row)
                {
                    treasure_coordinate = true;
                    break;
                }
            }

            // Imprime el símbolo correspondiente
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
    std::cout << "Leyenda: # = Sin explorar, $ = Tesoro, ! = Bomba\n";
}

// Función para modo multijugador
void game(std::vector<std::vector<int>> &bombXY)
{
    bool lose = false;
    int positionX = 0, positionY = 0, retire = 0;
    std::vector<int> coordinate;

    // Mostrar tablero inicial
    print_board();

    while (game_data.game_status)
    {
        for (int turn = 0; turn < game_data.max_players; ++turn)
        {
            if (players[turn].is_alive)
            {

                std::cout << "\nTurno de " << players[turn].name << " (Puntos: " << players[turn].points << ")\n";
                std::cout << "Ingrese sus coordenadas (X Y): \n";
                std::cout << "X: ";
                std::cin >> positionX;
                std::cout << "Y: ";
                std::cin >> positionY;

                coordinate = {positionX, positionY};

                // Verifica las coordenadas
                lose = prove_coordinates(coordinate, bombXY);
                game_data.repeat.push_back(coordinate);

                player_action(turn, lose);

                if (lose)
                {
                    game_over_message();
                    if (error_type.bombExplote)
                    {
                        players[turn].is_alive = false;
                        std::cout << players[turn].name << " ha perdido!\n";
                    }
                }
                else
                {
                    players[turn].points += 20;
                    std::cout << "¡Tesoro encontrado! +20 puntos\n";
                }

                print_board();

                if (players[turn].points >= 60 && players[turn].is_alive)
                {
                    std::cout << "¿Desea retirarse? (1=Sí, 0=No): ";
                    std::cin >> retire;
                    if (retire == 1)
                    {
                        players[turn].is_alive = false;
                    }
                }
            }
        }

        // Verificar si algún jugador sigue vivo
        game_data.game_status = false;
        for (int i = 0; i < game_data.max_players; i++)
        {
            if (players[i].is_alive)
            {
                game_data.game_status = true;
                break;
            }
        }
    }

    std::cout << "\n=== FIN DEL JUEGO ===\n";
    for (int i = 0; i < game_data.max_players; i++)
    {
        std::cout << players[i].name << ": " << players[i].points << " puntos\n";
    }
}