#include "save_load.h"
#include "configuration.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> // For system() command

void save_players_data(std::ofstream &archivo) // Saves the players data
{
    archivo << difficulty.max_rows << " " // Saves the maximum number of rows
            << difficulty.max_columns << " " // Saves the maximum number of columns
            << difficulty.max_bombs << " " // Saves the maximum number of bombs
            << difficulty.max_bullets << " " // Saves the maximum number of bullets
            << difficulty.max_shields << "\n"; // Saves the maximum number of shields

    archivo << game_data.max_players << "\n"; // Saves the maximum number of players
    for (int i = 0; i < game_data.max_players; i++)
    {
        archivo << players[i].name << " " // Saves the name of the player
                << players[i].points << " " // Saves the points of the player
                << players[i].bullets << " " // Saves the bullets of the player
                << players[i].shields << " " // Saves the shields of the player
                << players[i].action_shoot << " " // Saves the action to shoot
                << players[i].action_protect << " " // Saves the action to protect
                << players[i].excavate << " " // Saves the action to excavate
                << players[i].is_alive << "\n"; // Saves the state of the player
    }
}

void load_players_data(std::ifstream &archivo) // Loads the players data
{
    archivo >> difficulty.max_rows >> difficulty.max_columns >> difficulty.max_bombs >> difficulty.max_bullets >> difficulty.max_shields;

    archivo >> game_data.max_players;
    for (int i = 0; i < game_data.max_players; i++)
    {
        archivo >> players[i].name >> players[i].points >> players[i].bullets >> players[i].shields >> players[i].action_shoot >> players[i].action_protect >> players[i].excavate >> players[i].is_alive;
    }
}

void save_game(const std::vector<std::vector<int>> &bombXY) // Saves the game
{
    //Create saved_games directory if it doesn't exist (works on Windows)
    system("mkdir saved_games 2> nul");

    std::vector<std::string> existingFiles;
    for (int i = 1; i <= 3; i++)
    {
        // Modified: Added saved_games/ prefix to path
        std::string filename = "saved_games/partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (testFile.good())
        {
            existingFiles.push_back(filename);
        }
        testFile.close();
    }

    if (existingFiles.size() >= 3)
    {
        std::cout << "\nLimite de 3 partidas guardadas alcanzado!\n"; // Shows the limit of 3 saved games
        std::cout << "Partidas existentes:\n"; // Shows the existing games
        for (size_t i = 0; i < existingFiles.size(); i++)
        {
            std::cout << i + 1 << ". " << existingFiles[i] << "\n"; // Shows the existing games
        }

        std::cout << "Elija una opcion:\n"; // Shows the options
        std::cout << "1. Sobrescribir una partida existente\n"; // Shows the option to overwrite an existing game
        std::cout << "2. Cancelar guardado\n"; // Shows the option to cancel the save
        std::cout << "Opcion: "; // Shows the option
        int opcion;
        std::cin >> opcion;

        if (opcion != 1)
        {
            std::cout << "Guardado cancelado.\n"; // Shows the save canceled
            return;
        }

        std::cout << "Seleccione el numero de partida a sobrescribir (1-3): "; // Shows the option to overwrite an existing game
        int seleccion;
        std::cin >> seleccion;

        if (seleccion < 1 || seleccion > 3)
        {
            std::cout << "Opcion invalida. Guardado cancelado.\n"; // Shows the invalid option
            return;
        }

        // [MODIFIED] Added saved_games/ prefix to path
        std::string filename = "saved_games/partida" + std::to_string(seleccion) + ".txt";
        std::ofstream archivo(filename);
        if (!archivo)
        {
            std::cout << "No se pudo guardar la partida.\n"; // Shows the save failed
            return;
        }

        save_players_data(archivo);

        archivo << bombXY.size() << "\n";
        for (const std::vector<int> &coordinates : bombXY) // Saves the bomb coordinates
        {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.repeat.size() << "\n";
        for (const std::vector<int> &coordinates : game_data.repeat) // Saves the repeat coordinates
        {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.bomb_explote.size() << "\n";
        for (const std::vector<int> &coordinates : game_data.bomb_explote) // Saves the bomb explosion coordinates
        {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo << game_data.treasure_XY.size() << "\n";
        for (const std::vector<int> &coordinates : game_data.treasure_XY) // Saves the treasure coordinates
        {
            archivo << coordinates[0] << " " << coordinates[1] << "\n";
        }

        archivo.close();
        std::cout << "Partida guardada correctamente como " << filename << ".\n"; // Shows the save successful
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        std::string filename = "saved_games/partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (!testFile.good())
        {
            testFile.close();

            std::ofstream archivo(filename);
            if (!archivo)
            {
                std::cout << "No se pudo guardar la partida.\n"; // Shows the save failed
                return;
            }

            save_players_data(archivo);

            archivo << bombXY.size() << "\n";
            for (const std::vector<int> &coordinates : bombXY) // Saves the bomb coordinates
            {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.repeat.size() << "\n";
            for (const std::vector<int> &coordinates : game_data.repeat) // Saves the repeat coordinates
            {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.bomb_explote.size() << "\n";
            for (const std::vector<int> &coordinates : game_data.bomb_explote) // Saves the bomb explosion coordinates
            {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo << game_data.treasure_XY.size() << "\n";
            for (const std::vector<int> &coordinates : game_data.treasure_XY) // Saves the treasure coordinates
            {
                archivo << coordinates[0] << " " << coordinates[1] << "\n";
            }

            archivo.close();
            std::cout << "Partida guardada correctamente como " << filename << ".\n"; // Shows the save successful
            return;
        }
        testFile.close();
    }
}

void load_game(std::vector<std::vector<int>> &bombXY) // Loads the game
{
    std::cout << "\n=== PARTIDAS GUARDADAS ===\n";
    std::vector<std::string> availableFiles;

    for (int i = 1; i <= 3; i++)
    {
        // [MODIFIED] Added saved_games/ prefix to path
        std::string filename = "saved_games/partida" + std::to_string(i) + ".txt";
        std::ifstream testFile(filename);
        if (testFile.good())
        {
            std::cout << i << ". " << filename << "\n";
            availableFiles.push_back(filename);
        }
        testFile.close();
    }

    if (availableFiles.empty())
    {
        std::cout << "No hay partidas guardadas disponibles.\n"; // Shows the no saved games
        save_load.game_load = false;
        return;
    }

    std::cout << "Seleccione el numero de partida a cargar (1-" << availableFiles.size() << "): "; // Shows the option to load a game
    int selected;
    std::cin >> selected;

    if (selected < 1 || selected > availableFiles.size())
    {
        std::cout << "Opcion invalida.\n"; // Shows the invalid option
        return;
    }

    std::string selectedFile = availableFiles[selected - 1];
    std::ifstream archivo(selectedFile);

    if (!archivo)
    {
        std::cout << "Error al abrir el archivo.\n"; // Shows the error opening the file
        save_load.game_load = false;
        return;
    }

    load_players_data(archivo);

    auto loadCoordinates = [&archivo](std::vector<std::vector<int>> &vec) // Loads the coordinates
    {
        int count;
        if (!(archivo >> count)) // Checks if the count is valid
            return false;

        vec.resize(count);
        for (int i = 0; i < count; i++) // Loads the coordinates
        {
            int x, y;
            if (!(archivo >> x >> y)) // Checks if the coordinates are valid
                return false;
            vec[i] = {x, y}; // Loads the coordinates
        }
        return true;
    };

    if (!loadCoordinates(bombXY) || // Loads the bomb coordinates
        !loadCoordinates(game_data.repeat) || // Loads the repeat coordinates
        !loadCoordinates(game_data.bomb_explote) || // Loads the bomb explosion coordinates
        !loadCoordinates(game_data.treasure_XY)) // Loads the treasure coordinates
    {
        std::cout << "Error leyendo datos de partida.\n"; // Shows the error reading the game data
        return;
    }

    archivo.close(); // Closes the file
    std::cout << "Partida cargada exitosamente desde " << selectedFile << "\n"; // Shows the game loaded successfully
    save_load.game_load = true; // Sets the game load to true
}