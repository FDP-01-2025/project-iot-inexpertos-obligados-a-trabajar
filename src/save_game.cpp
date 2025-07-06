#include "save_game.h"
#include "configuration.h"
#include <fstream>
#include <iostream>

// Función para guardar partida
void save_game(const std::vector<std::vector<int>> &bombXY) {
    std::vector<std::string> existingFiles;
    for (int i = 1; i <= 3; i++) {
        std::string filename = "partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (testFile.good()) {
            existingFiles.push_back(filename);
        }
        testFile.close();
    }

    if (existingFiles.size() >= 3) {
        std::cout << "\n¡Límite de 3 partidas guardadas alcanzado!\n";
        std::cout << "Partidas existentes:\n";
        for (int i = 0; i < existingFiles.size(); i++) {
            std::cout << i + 1 << ". " << existingFiles[i] << "\n";
        }

        std::cout << "Elija una opción:\n";
        std::cout << "1. Sobrescribir una partida existente\n";
        std::cout << "2. Cancelar guardado\n";
        std::cout << "Opción: ";
        int opcion;
        std::cin >> opcion;

        if (opcion != 1) {
            std::cout << "Guardado cancelado.\n";
            return;
        }

        std::cout << "Seleccione el número de partida a sobrescribir (1-3): ";
        int seleccion;
        std::cin >> seleccion;

        if (seleccion < 1 || seleccion > 3) {
            std::cout << "Opción inválida. Guardado cancelado.\n";
            return;
        }

        std::string filename = "partida" + std::to_string(seleccion) + ".txt";
        std::ofstream archivo(filename);
        if (!archivo) {
            std::cout << "No se pudo guardar la partida.\n";
            return;
        }

        archivo << difficulty.max_rows << " " << difficulty.max_columns << " " << difficulty.max_bombs << "\n";

        archivo << bombXY.size() << "\n";
        for (const auto &coordinates : bombXY) {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.repeat.size() << "\n";
        for (const auto &coordinates : game_data.repeat) {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.bomb_explote.size() << "\n";
        for (const auto &coordinates : game_data.bomb_explote) {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.treasure_XY.size() << "\n";
        for (const auto &coordinates : game_data.treasure_XY) {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo.close();
        std::cout << "Partida guardada correctamente como " << filename << ".\n";
        return;
    }

    for (int i = 1; i <= 3; i++) {
        std::string filename = "partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (!testFile.good()) {
            testFile.close();

            std::ofstream archivo(filename);
            if (!archivo) {
                std::cout << "No se pudo guardar la partida.\n";
                return;
            }

            archivo << difficulty.max_rows << " " << difficulty.max_columns << " " << difficulty.max_bombs << "\n";
            archivo << bombXY.size() << "\n";
            for (const auto &coordinates : bombXY) {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.repeat.size() << "\n";
            for (const auto &coordinates : game_data.repeat) {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.bomb_explote.size() << "\n";
            for (const auto &coordinates : game_data.bomb_explote) {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.treasure_XY.size() << "\n";
            for (const auto &coordinates : game_data.treasure_XY) {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo.close();
            std::cout << "Partida guardada correctamente como " << filename << ".\n";
            return;
        }
        testFile.close();
    }
}

// Función para cargar partida
void load_game(std::vector<std::vector<int>> &bombXY) {
    std::cout << "\n=== PARTIDAS GUARDADAS ===\n";
    std::vector<std::string> availableFiles;

    for (int i = 1; i <= 3; i++) {
        std::string filename = "partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (testFile.good()) {
            std::cout << i << ". " << filename << "\n";
            availableFiles.push_back(filename);
        }
        testFile.close();
    }

    if (availableFiles.empty()) {
        std::cout << "No hay partidas guardadas disponibles.\n";
        return;
    }

    std::cout << "Seleccione el número de partida a cargar (1-" << availableFiles.size() << "): ";
    int selected;
    std::cin >> selected;

    if (selected < 1 || selected > availableFiles.size()) {
        std::cout << "Opción inválida.\n";
        return;
    }

    std::string selectedFile = availableFiles[selected - 1];
    std::ifstream archivo(selectedFile);

    if (!archivo) {
        std::cout << "Error al abrir el archivo.\n";
        return;
    }

    // Resetear el estado del juego
    game_data.reset();
    bombXY.clear();

    // Leer configuración de dificultad
    if (!(archivo >> difficulty.max_rows >> difficulty.max_columns >> difficulty.max_bombs)) {
        std::cout << "Error leyendo configuración de dificultad.\n";
        return;
    }

    // Función lambda para cargar coordenadas
    auto loadCoordinates = [&archivo](std::vector<std::vector<int>> &vec) {
        int count;
        if (!(archivo >> count)) return false;

        vec.resize(count);
        for (int i = 0; i < count; i++) {
            int x, y;
            if (!(archivo >> x >> y)) return false;
            vec[i] = {x, y};
        }
        return true;
    };

    // Cargar todas las coordenadas
    if (!loadCoordinates(bombXY) ||
        !loadCoordinates(game_data.repeat) ||
        !loadCoordinates(game_data.bomb_explote) ||
        !loadCoordinates(game_data.treasure_XY)) {
        std::cout << "Error leyendo datos de partida.\n";
        game_data.reset();
        bombXY.clear();
        return;
    }

    archivo.close();
    std::cout << "Partida cargada exitosamente desde " << selectedFile << "\n";
}