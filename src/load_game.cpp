#include "load_game.h"
#include "configuration.h"
#include "players.h"
#include <fstream>
#include <iostream>

void load_game(std::vector<std::vector<int>>& bombXY) {
    std::ifstream file("partida.txt");
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo de partida para cargar.\n";
        return;
    }

    bombXY.clear();
    game_data.reset();
    difficulty.reset();

    std::string line;

    // Limpio jugadores por si acaso
    for (int i = 0; i < 4; i++) {
        players[i].is_alive = false;
        players[i].points = 0;
    }
}
