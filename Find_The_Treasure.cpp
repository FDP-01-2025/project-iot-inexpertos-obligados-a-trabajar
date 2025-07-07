#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// Estructura para manejar la dificultad del juego
struct Difficulty {
    int maxRows;    // Número máximo de filas
    int maxColumns; // Número máximo de columnas
    int maxBombs;   // Número máximo de bombas
    int maxBullets; // Número máximo de balas
    int maxShields; // Número máximo de escudos
    void reset() {
        maxRows = 0;
        maxColumns = 0;
        maxBombs = 0;
        maxBullets = 0;
        maxShields = 0;
    }
} difficulty;

// Estructura para manejar información del juego
struct GameData {
    int max_players;
    bool game_status = true;
    vector<vector<int>> bomb_explote;
    vector<vector<int>> repeat;
    vector<vector<int>> treasureXY;

    void reset() {
        bomb_explote.clear();
        repeat.clear();
        treasureXY.clear();
    }
} game_data;

// Estructura para manejar información de jugadores
struct Players {
    string name;    // Nombre del jugador
    int points;     // Puntos acumulados
    int bullets;    // Balas disponibles
    int shields;    // Escudos disponibles
    bool action_shoot; // Acción de disparar
    bool action_protect; // Acción de proteger
    bool excavate;  // Acción de excavar
    bool is_alive;  // Indica si el jugador está vivo

    void actions_reset() {
        action_shoot = false;
        action_protect = false;
        excavate = false;
    }
} players[5];

// Estructura para manejar el estado del juego
struct ErrorType {
    bool bombExplote;
    bool repeatCoordinate;
    bool outOfRange;
    bool dataTypeInvalid;

    void reset() {
        bombExplote = false;
        repeatCoordinate = false;
        outOfRange = false;
        dataTypeInvalid = false;
    }
} error_type;

// Función para guardar datos de los jugadores
void save_players_data(ofstream &archivo) {
    archivo << difficulty.maxRows << " " 
            << difficulty.maxColumns << " " 
            << difficulty.maxBombs << " "
            << difficulty.maxBullets << " "
            << difficulty.maxShields << "\n";
            
    archivo << game_data.max_players << "\n";
    for (int i = 0; i < game_data.max_players; i++) {
        archivo << players[i].name << " " 
                << players[i].points << " " 
                << players[i].bullets << " " 
                << players[i].shields << " "
                << players[i].action_shoot << " "
                << players[i].action_protect << " "
                << players[i].excavate << " "
                << players[i].is_alive << "\n";
    }
}

// Función para cargar datos de los jugadores
void load_players_data(ifstream &archivo) {
    archivo >> difficulty.maxRows 
            >> difficulty.maxColumns 
            >> difficulty.maxBombs
            >> difficulty.maxBullets
            >> difficulty.maxShields;
            
    archivo >> game_data.max_players;
    for (int i = 0; i < game_data.max_players; i++) {
        archivo >> players[i].name 
                >> players[i].points 
                >> players[i].bullets 
                >> players[i].shields
                >> players[i].action_shoot
                >> players[i].action_protect
                >> players[i].excavate
                >> players[i].is_alive;
    }
}

// Prototipos de funciones
void print_board();
int game_menu();
void menu_difficulty(int dif);
vector<vector<int>> random_coordinates();
bool prove_coordinates(const vector<int> &coordinate, const vector<vector<int>> &bombXY);
void game_over_message();
string sprite(string typeSprite);
bool victory(int points, int playerIndex = -1);
void save_game(const vector<vector<int>> &bombXY);
void load_game(vector<vector<int>> &bombXY);
void game_multiplayer(vector<vector<int>> &bombXY);
void reset_game_state(vector<vector<int>> &bombXY);
void pistol_shot(int &turn, bool &lose);
void shield_protection(int &turn, bool &lose);
void player_action(int &turn, bool &lose, vector<vector<int>> &bombXY);
void player_configuration();
bool show_post_save_menu();

int main()
{
    srand(time(NULL));
    sprite("Title");
    game_menu();
    return 0;
}

// Función para mostrar sprites del juego
string sprite(string typeSprite)
{
    if (typeSprite == "Title")
    {
        cout << " ___                                                                      ___ \n"
                "( _ )--------------------------------------------------------------------( _ )\n"
                " | |                                                                      | | \n"
                " | |                                                                      | | \n"
                " | |   ######  ######  ##  ##  #####           ######  ##  ##  ######     | | \n"
                " | |   ##        ##    ### ##  ##  ##            ##    ##  ##  ##         | | \n"
                " | |   ####      ##    ## ###  ##  ##            ##    ######  ####       | | \n"
                " | |   ##        ##    ##  ##  ##  ##            ##    ##  ##  ##         | | \n"
                " | |   ##      ######  ##  ##  #####             ##    ##  ##  ######     | | \n"
                " | |   ................................................................   | | \n"
                " | |   ######  #####   ######   ####    ####    ##  ##  #####   ######    | | \n"
                " | |     ##    ##  ##  ##      ##  ##  ##       ##  ##  ##  ##  ##        | | \n"
                " | |     ##    #####   ####    ######   ####    ##  ##  #####   ####      | | \n"
                " | |     ##    ##  ##  ##      ##  ##      ##   ##  ##  ##  ##  ##        | | \n"
                " | |     ##    ##  ##  ######  ##  ##   ####     ####   ##  ##  ######    | | \n"
                " | |   ................................................................   | | \n"
                " | |                                                                      | | \n"
                " |_|                                                                      |_| \n"
                "(___)--------------------------------------------------------------------(___)\n";
    }
    else if (typeSprite == "Bomb")
    {
        cout << R"(
         _.-^^---....,,--       
     _--                  --_  
    <                        >)
    |                         | 
     \._                   _./  
        ```--. . , ; .--'''       
              | |   |             
           .-=||  | |=-.   
           `-=#$%&%$#=-'   
              | ;  :|     
     _____.,-#%&$@%#&#~,._____
        )" << endl;
    }
    else if (typeSprite == "Treasure")
    {
        cout << R"(
       /\
      /  \
     /    \
    /      \
    \      /
     \    /
      \  /
       \/
    )" << endl;
    }
    else if (typeSprite == "Shield")
    {
        cout << R"(
       _,--`--,_
     ,'    _    `.
    /    _/ \_    \
   |    /     \    |
   |   |       |   |
   |   |       |   |
    \   \     /   /
     `.  `---'  ,'
       `-.____.-'
        )" << endl;
    }
    else if (typeSprite == "Pistol")
    {
        cout << R"(
        _______ 
       /       \__________________________________
      /        |                                 |
     |_________|                                 |
     |   |     |                                 |
     |   |     |=======>                         |
     |___|_____|_________________________________|
        |     |
        |_____|
        )" << endl;
    }
    else if (typeSprite == "GameOver")
    {
        cout << R"(
       __________________________
      /                         /
     /        GAME OVER        /
    /_________________________/
    )" << endl;
    }
    else if (typeSprite == "Winner")
    {
        cout << R"(
            .-===========-. 
         (                  )
          |       #1       |
          |                |
          |    ________    |
          |                |
           \     ____     /
            \   \    /   /
             '.  \  /  .'
               '._\/_.'
                  ||
                  ||
               .-'  '--.
              /        \
             |   WIN    |
              \        /
               '-____-'
    )" << endl;
    }
    else if (typeSprite == "Explosion")
    {
        cout << R"(
           .-^---.
         .'       `.
        /           \
       |    BOOM!    |
        \           /
         `.       .'
           `-...-'
        )" << endl;
    }
    return "";
}

// Función para configurar la dificultad del juego
void menu_difficulty(int dif)
{
    switch (dif)
    {
    case 1: // Fácil
        difficulty.maxRows = 10;
        difficulty.maxColumns = 10;
        difficulty.maxBombs = 30;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    case 2: // Medio
        difficulty.maxRows = 20;
        difficulty.maxColumns = 20;
        difficulty.maxBombs = 80;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    case 3: // Difícil
        difficulty.maxRows = 30;
        difficulty.maxColumns = 30;
        difficulty.maxBombs = 100;
        difficulty.maxBullets = 10;
        difficulty.maxShields = 5;
        break;
    default: // Multijugador
        break;
    }
}

// Función para generar coordenadas aleatorias de bombas
vector<vector<int>> random_coordinates()
{
    vector<vector<int>> bombXY;
    int bombsTotal = difficulty.maxBombs;

    while (bombXY.size() < bombsTotal)
    {
        int bombX = rand() % difficulty.maxRows + 1;
        int bombY = rand() % difficulty.maxColumns + 1;
        vector<int> candidate = {bombX, bombY};

        if (find(bombXY.begin(), bombXY.end(), candidate) == bombXY.end())
        {
            bombXY.push_back(candidate);
        }
    }
    return bombXY;
}

// Función para verificar coordenadas ingresadas
bool prove_coordinates(const vector<int> &coordinate, const vector<vector<int>> &bombXY)
{
    if ((coordinate[0] <= 0 || coordinate[0] > difficulty.maxColumns) ||
        (coordinate[1] <= 0 || coordinate[1] > difficulty.maxRows))
    {
        error_type.outOfRange = true;
        return true;
    }

    if (find(game_data.repeat.begin(), game_data.repeat.end(), coordinate) != game_data.repeat.end())
    {
        error_type.repeatCoordinate = true;
        return true;
    }

    if (find(bombXY.begin(), bombXY.end(), coordinate) != bombXY.end())
    {
        game_data.bomb_explote.push_back(coordinate);
        error_type.bombExplote = true;
        sprite("Bomb");
        sprite("Explosion");
        return true;
    }

    game_data.treasureXY.push_back(coordinate);
    sprite("Treasure");
    return false;
}

// Función para mostrar mensaje de fin de juego
void game_over_message()
{
    if (error_type.bombExplote)
    {
        sprite("GameOver");
        cout << "¡Has pisado una bomba!\n";
    }
    else if (error_type.repeatCoordinate)
    {
        cout << "¡Coordenada repetida! No es válido.\n";
    }
    else if (error_type.outOfRange)
    {
        cout << "¡Coordenada fuera del rango establecido!\n";
    }
    else if (error_type.dataTypeInvalid)
    {
        cout << "Dato inválido. Debe ingresar un número entero dentro del rango.\n";
    }
}

// Función para mostrar la pantalla de victoria
bool victory(int points, int playerIndex)
{
    sprite("Winner");

    // Crear vector de pares (puntos, nombre) para ordenar
    vector<pair<int, string>> rankings;
    for (int i = 0; i < game_data.max_players; i++) {
        rankings.emplace_back(players[i].points, players[i].name);
    }

    // Ordenar de mayor a menor
    sort(rankings.rbegin(), rankings.rend());

    cout << "\n=== TABLA DE POSICIONES ===\n";
    for (size_t i = 0; i < rankings.size(); i++) {
        cout << i+1 << ". " << rankings[i].second << ": " << rankings[i].first << " puntos\n";
    }

    if (playerIndex >= 0) {
        // Mostrar mensaje personalizado para el ganador
        cout << "\n¡FELICIDADES " << players[playerIndex].name << " HAS GANADO!\n";
    } else {
        cout << "\n¡HAS GANADO!\n";
    }

    cout << "Puntos finales: " << points << "\n";
    print_board();

    // Preguntar si quiere jugar otra partida
    cout << "\n¿Desea jugar otra partida? (1=Sí, 0=No): ";
    int opcion;
    cin >> opcion;
    if (opcion == 1) {
        vector<vector<int>> newBombXY;
        reset_game_state(newBombXY);
        game_menu();
    }

    return true;
}

// Función para guardar la partida (VERSIÓN CORREGIDA)
void save_game(const vector<vector<int>> &bombXY)
{
    // Crear directorio de guardado si no existe
    #ifdef _WIN32
        system("mkdir partidas_guardadas 2>nul");
    #else
        system("mkdir -p partidas_guardadas");
    #endif

    vector<string> existingFiles;
    for (int i = 1; i <= 3; i++)
    {
        string filename = "partidas_guardadas/partida" + to_string(i) + ".txt";
        ifstream testFile(filename);
        if (testFile.good())
        {
            existingFiles.push_back(filename);
        }
        testFile.close();
    }

    string filename;
    if (existingFiles.size() >= 3)
    {
        cout << "\n¡Límite de 3 partidas guardadas alcanzado!\n";
        cout << "Partidas existentes:\n";
        for (int i = 0; i < existingFiles.size(); i++)
        {
            cout << i + 1 << ". " << existingFiles[i] << "\n";
        }

        cout << "Elija una opción:\n";
        cout << "1. Sobrescribir una partida existente\n";
        cout << "2. Cancelar guardado\n";
        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        if (opcion != 1)
        {
            cout << "Guardado cancelado.\n";
            return;
        }

        cout << "Seleccione el número de partida a sobrescribir (1-3): ";
        int seleccion;
        cin >> seleccion;

        if (seleccion < 1 || seleccion > 3)
        {
            cout << "Opción inválida. Guardado cancelado.\n";
            return;
        }

        filename = "partidas_guardadas/partida" + to_string(seleccion) + ".txt";
    }
    else
    {
        // Buscar el primer slot disponible
        for (int i = 1; i <= 3; i++)
        {
            filename = "partidas_guardadas/partida" + to_string(i) + ".txt";
            ifstream testFile(filename);
            if (!testFile.good())
            {
                testFile.close();
                break;
            }
            testFile.close();
        }
    }

    ofstream archivo(filename);
    if (!archivo)
    {
        cout << "Error: No se pudo crear el archivo de guardado.\n";
        cout << "Asegúrese de tener permisos de escritura en el directorio.\n";
        return;
    }

    // Guardar datos de dificultad y jugadores
    save_players_data(archivo);

    // Guardar coordenadas de bombas
    archivo << bombXY.size() << "\n";
    for (const auto &coord : bombXY)
    {
        archivo << coord[0] << " " << coord[1] << "\n";
    }

    // Guardar coordenadas repetidas
    archivo << game_data.repeat.size() << "\n";
    for (const auto &coord : game_data.repeat)
    {
        archivo << coord[0] << " " << coord[1] << "\n";
    }

    // Guardar bombas explotadas
    archivo << game_data.bomb_explote.size() << "\n";
    for (const auto &coord : game_data.bomb_explote)
    {
        archivo << coord[0] << " " << coord[1] << "\n";
    }

    // Guardar tesoros encontrados
    archivo << game_data.treasureXY.size() << "\n";
    for (const auto &coord : game_data.treasureXY)
    {
        archivo << coord[0] << " " << coord[1] << "\n";
    }

    archivo.close();
    cout << "\nPartida guardada correctamente en: " << filename << "\n";

    // Mostrar menú post-guardado
    if (show_post_save_menu()) {
        exit(0);
    }
}

// Función para cargar una partida guardada
void load_game(vector<vector<int>> &bombXY)
{
    cout << "\n=== PARTIDAS GUARDADAS ===\n";
    vector<string> availableFiles;

    for (int i = 1; i <= 3; i++)
    {
        string filename = "partidas_guardadas/partida" + to_string(i) + ".txt";
        ifstream testFile(filename);
        if (testFile.good())
        {
            cout << i << ". " << filename << "\n";
            availableFiles.push_back(filename);
        }
        testFile.close();
    }

    if (availableFiles.empty())
    {
        cout << "No hay partidas guardadas disponibles.\n";
        return;
    }

    cout << "Seleccione el número de partida a cargar (1-" << availableFiles.size() << "): ";
    int selected;
    cin >> selected;

    if (selected < 1 || selected > availableFiles.size())
    {
        cout << "Opción inválida.\n";
        return;
    }

    string selectedFile = availableFiles[selected - 1];
    ifstream archivo(selectedFile);

    if (!archivo)
    {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    reset_game_state(bombXY);

    load_players_data(archivo);

    auto loadCoordinates = [&archivo](vector<vector<int>> &vec)
    {
        int count;
        if (!(archivo >> count))
            return false;

        vec.resize(count);
        for (int i = 0; i < count; i++)
        {
            int x, y;
            if (!(archivo >> x >> y))
                return false;
            vec[i] = {x, y};
        }
        return true;
    };

    if (!loadCoordinates(bombXY) ||
        !loadCoordinates(game_data.repeat) ||
        !loadCoordinates(game_data.bomb_explote) ||
        !loadCoordinates(game_data.treasureXY))
    {
        cout << "Error leyendo datos de partida.\n";
        reset_game_state(bombXY);
        return;
    }

    archivo.close();
    cout << "Partida cargada exitosamente desde " << selectedFile << "\n";

    print_board();
    game_multiplayer(bombXY);
}

// Función para imprimir el tablero de juego
void print_board()
{
    bool bomb_coordinate, treasure_coordinate;

    cout << "\n=== TABLERO DE JUEGO ===\n";
    cout << "   ";
    for (int col = 1; col <= difficulty.maxColumns; col++)
    {
        if (col < 10)
            cout << " " << col << " ";
        else
            cout << col << " ";
    }
    cout << endl;

    for (int row = 1; row <= difficulty.maxRows; row++)
    {
        if (row < 10)
            cout << " " << row << " ";
        else
            cout << row << " ";

        for (int column = 1; column <= difficulty.maxColumns; column++)
        {
            bomb_coordinate = false;
            treasure_coordinate = false;

            for (const vector<int> &bomb : game_data.bomb_explote)
            {
                if (bomb[0] == column && bomb[1] == row)
                {
                    bomb_coordinate = true;
                    break;
                }
            }

            for (const vector<int> &treasure : game_data.treasureXY)
            {
                if (treasure[0] == column && treasure[1] == row)
                {
                    treasure_coordinate = true;
                    break;
                }
            }

            bool explored = find(game_data.repeat.begin(), game_data.repeat.end(), vector<int>{column, row}) != game_data.repeat.end();

            if (bomb_coordinate)
            {
                cout << " ! ";
            }
            else if (treasure_coordinate)
            {
                cout << " $ ";
            }
            else if (explored)
            {
                cout << " . ";
            }
            else
            {
                cout << " # ";
            }
        }
        cout << endl;
    }
    cout << "Leyenda: # = Sin explorar, $ = Tesoro, ! = Bomba, . = Explorado\n";
}

// Función para mostrar el menú principal del juego
int game_menu()
{
    int opcion;
    vector<vector<int>> bombXY;

    while (true)
    {
        cout << R"( 
   --------------------------------------------
 |        ENCUENTRA EL TESORO                  |
 |---------------------------------------------|
 | 1. Jugar modo Solitario                     |
 | 2. Jugar modo Multijugador                  |
 | 3. Salir del juego                          |
   -------------------------------------------- 
Seleccione una opción: )";
        cin >> opcion;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada inválida. Por favor ingrese un número.\n";
            continue;
        }

        if (opcion == 1)
        {
            reset_game_state(bombXY);
            game_data.max_players = 1;

            int dif;
            cout << "\nSelecciona dificultad:\n";
            cout << "1. Fácil (10x10 - 30 bombas)\n";
            cout << "2. Medio (20x20 - 80 bombas)\n";
            cout << "3. Difícil (30x30 - 100 bombas)\n";
            cout << "Opción: ";
            cin >> dif;

            menu_difficulty(dif);
            bombXY = random_coordinates();
            player_configuration();
            game_multiplayer(bombXY);
        }
        else if (opcion == 2)
        {
            reset_game_state(bombXY);

            int dif;
            cout << "\nSelecciona dificultad para Multijugador:\n";
            cout << "1. Fácil (10x10 - 30 bombas)\n";
            cout << "2. Medio (20x20 - 80 bombas)\n";
            cout << "3. Difícil (30x30 - 100 bombas)\n";
            cout << "Opción: ";
            cin >> dif;

            cout << "\n¿Con cuántos jugadores deseas jugar? (1-4): ";
            cin >> game_data.max_players;

            if (game_data.max_players < 1 || game_data.max_players > 4)
            {
                cout << "Número de jugadores inválido. Debe ser entre 1 y 4.\n";
                continue;
            }

            menu_difficulty(dif);
            player_configuration();
            bombXY = random_coordinates();
            game_multiplayer(bombXY);
        }
        else if (opcion == 3)
        {
            cout << "¡Gracias por jugar! Hasta la próxima.\n";
            exit(0);
        }
        else
        {
            cout << "Opción no válida. Intenta de nuevo.\n";
        }
    }

    return 0;
}

// Función para el modo multijugador
void game_multiplayer(vector<vector<int>> &bombXY)
{
    bool lose = false;
    int positionX = 0, positionY = 0, retire = 0;
    vector<int> coordinate;

    print_board();

    while (game_data.game_status)
    {
        for (int turn = 0; turn < game_data.max_players; ++turn)
        {
            if (players[turn].is_alive)
            {
                cout << "\nTurno de " << players[turn].name << " (Puntos: " << players[turn].points << ")\n";
                cout << "Balas: " << players[turn].bullets << " | Escudos: " << players[turn].shields << endl;
                cout << "Ingrese sus coordenadas (X Y): \n";
                cout << "X: ";
                cin >> positionX;
                cout << "Y: ";
                cin >> positionY;

                coordinate = {positionX, positionY};

                lose = prove_coordinates(coordinate, bombXY);
                game_data.repeat.push_back(coordinate);

                player_action(turn, lose, bombXY);

                if (lose)
                {
                    game_over_message();
                    if (error_type.bombExplote)
                    {
                        players[turn].is_alive = false;
                        cout << players[turn].name << " ha perdido!\n";
                    }
                }
                else
                {
                    players[turn].points += 20;
                    cout << "¡Tesoro encontrado! +20 puntos\n";
                }

                print_board();

                if (players[turn].points >= 60 && players[turn].is_alive)
                {
                    cout << "¿Desea retirarse? (1=Sí, 0=No): ";
                    cin >> retire;
                    if (retire == 1)
                    {
                        victory(players[turn].points, turn);
                        players[turn].is_alive = false;
                    }
                }
            }
        }

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

    int maxPoints = -1;
    int winnerIndex = -1;
    for (int i = 0; i < game_data.max_players; i++)
    {
        if (players[i].points > maxPoints)
        {
            maxPoints = players[i].points;
            winnerIndex = i;
        }
    }

    if (winnerIndex != -1)
    {
        victory(players[winnerIndex].points, winnerIndex);
    }
}

// Función para configurar los jugadores
void player_configuration()
{
    for (int i = 0; i < game_data.max_players; i++)
    {
        bool validName = false;
        while (!validName)
        {
            cout << "Nombre del jugador " << i + 1 << " (máx 20 caracteres, sin espacios): ";
            cin >> players[i].name;
            
            // Validar el nombre
            if (players[i].name.empty())
            {
                cout << "Error: El nombre no puede estar vacío.\n";
            }
            else if (players[i].name.length() > 20)
            {
                cout << "Error: El nombre es demasiado largo (máximo 20 caracteres).\n";
            }
            else
            {
                validName = true;
            }
            
            // Limpiar el buffer de entrada en caso de errores
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        players[i].points = 0;
        players[i].bullets = difficulty.maxBullets;
        players[i].shields = difficulty.maxShields;
        players[i].action_shoot = false;
        players[i].action_protect = false;
        players[i].excavate = false;
        players[i].is_alive = true;
        
        cout << "Jugador " << players[i].name << " creado con éxito!\n";
    }
}

// Función para reiniciar el estado del juego
void reset_game_state(vector<vector<int>> &bombXY)
{
    game_data.reset();
    error_type.reset();
    bombXY.clear();
    
    for (int i = 0; i < 5; i++)
    {
        players[i].name = "";
        players[i].points = 0;
        players[i].bullets = 0;
        players[i].shields = 0;
        players[i].action_shoot = false;
        players[i].action_protect = false;
        players[i].excavate = false;
        players[i].is_alive = false;
    }
    
    difficulty.reset();
}

// Función para manejar el disparo con pistola
void pistol_shot(int &turn, bool &lose)
{
    if (players[turn].bullets == 0)
    {
        cout << players[turn].name << " no tiene balas, no puede disparar\n";
        return;
    }
    else if (lose)
    {
        sprite("Pistol");
        cout << players[turn].name << " a hecho explotar una bomba! +10 puntos\n";
    }
    else
    {
        sprite("Pistol");
        cout << players[turn].name << " a desperdiciado una bala!, no gana puntos\n";
    }

    players[turn].bullets--;
    lose = false;
}

// Función para manejar la protección con escudo
void shield_protection(int &turn, bool &lose)
{
    if (players[turn].shields == 0)
    {
        cout << players[turn].name << " no tiene escudos, no puede protegerse\n";
        return;
    }
    else if (lose)
    {
        sprite("Shield");
        cout << players[turn].name << " se ha protegido de una bomba! +10 puntos\n";
        players[turn].shields--;
        lose = false;
    }
    else
    {
        sprite("Shield");
        cout << players[turn].name << " a gastado un escudo, no gana puntos\n";
        players[turn].shields--;
        lose = false;
    }
}

// Función para manejar las acciones del jugador
void player_action(int &turn, bool &lose, vector<vector<int>> &bombXY)
{
    int action;
    while (true)
    {
        cout << "¿Qué desea hacer?\n";
        cout << "1. Excavar\n";
        cout << "2. Protegerse (Escudos: " << players[turn].shields << ")\n";
        cout << "3. Disparar con pistola (Balas: " << players[turn].bullets << ")\n";
        cout << "4. Guardar partida y salir\n";
        cout << "5. Cargar partida guardada\n";
        cout << "Opción: ";
        cin >> action;

        if (action >= 1 && action <= 5)
            break;
        cout << "Opción inválida. Intente nuevamente.\n";
    }

    switch (action)
    {
    case 1: // Excavar
        players[turn].excavate = true;
        players[turn].action_shoot = false;
        players[turn].action_protect = false;
        cout << "Usted ha excavado... \n";
        break;
    case 2: // Protegerse
        players[turn].action_protect = true;
        players[turn].excavate = false;
        players[turn].action_shoot = false;
        shield_protection(turn, lose);
        break;
    case 3: // Disparar con pistola
        players[turn].action_shoot = true;
        players[turn].excavate = false;
        players[turn].action_protect = false;
        pistol_shot(turn, lose);
        break;
    case 4: // Guardar partida y salir
        save_game(bombXY);
        return;
    case 5: // Cargar partida guardada
        load_game(bombXY);
        return;
    }
}

// Función para mostrar el menú después de guardar
bool show_post_save_menu()
{
    system("cls");
    while (true)
    {
               cout << R"( 
              --------------------------------------------
            |            PARTIDA GUARDADA                 |
            |---------------------------------------------|
            | 1. Iniciar nueva partida                    |
            | 2. Cargar partida guardada                  |
            | 3. Salir del juego                          |
              -------------------------------------------- 
Seleccione una opción: )";
        int opcion;
        cin >> opcion;

        vector<vector<int>> bombXY;

        switch (opcion)
        {
        case 1:
            reset_game_state(bombXY);
            game_menu();
            return false;
        case 2:
            load_game(bombXY);
            return false;
        case 3:
            return true;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    }
}