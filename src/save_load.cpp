#include "save_load.h"
#include <fstream>

void save_game(const std::vector<std::vector<int>>& bombXY) {
    std::ofstream file("partida.txt");
    // Implementación aquí (guardar coordenadas de bombas)
}

void load_game(std::vector<std::vector<int>>& bombXY) {
    std::ifstream file("partida.txt");
    // Implementación aquí (cargar coordenadas de bombas)
}