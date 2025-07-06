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
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("max_players=") == 0) {
            game_data.max_players = std::stoi(line.substr(12));
        }
        else if (line.find("difficulty_rows=") == 0) {
            difficulty.max_rows = std::stoi(line.substr(16));
        }
        else if (line.find("difficulty_columns=") == 0) {
            difficulty.max_columns = std::stoi(line.substr(19));
        }
        else if (line.find("difficulty_bombs=") == 0) {
            difficulty.max_bombs = std::stoi(line.substr(17));
        }
        else if (line.find("difficulty_bullets=") == 0) {
            difficulty.max_bullets = std::stoi(line.substr(19));
        }
        else if (line.find("difficulty_shields=") == 0) {
            difficulty.max_shields = std::stoi(line.substr(19));
        }
        else if (line.find("player") == 0 && line.find("_name=") != std::string::npos) {
            size_t p1 = line.find("player") + 6;
            size_t p2 = line.find("_name=");
            int idx = std::stoi(line.substr(p1, p2 - p1));
            std::string name = line.substr(p2 + 6);
            if (idx >=0 && idx < 4) {
                players[idx].name = name;
                players[idx].is_alive = true;
            }
        }
        else if (line.find("player") == 0 && line.find("_points=") != std::string::npos) {
            size_t p1 = line.find("player") + 6;
            size_t p2 = line.find("_points=");
            int idx = std::stoi(line.substr(p1, p2 - p1));
            int pts = std::stoi(line.substr(p2 + 8));
            if (idx >= 0 && idx < 4) {
                players[idx].points = pts;
            }
            else if (line.find("bomb=") == 0) {
            std::string coords = line.substr(5);
            size_t coma = coords.find(',');
            if (coma != std::string::npos) {
                int x = std::stoi(coords.substr(0, coma));
                int y = std::stoi(coords.substr(coma + 1));
                bombXY.push_back({x, y});
            }
        }
    }

    game_data.game_status = true;

    std::cout << "Partida cargada con éxito.\n";
}
        }
}
