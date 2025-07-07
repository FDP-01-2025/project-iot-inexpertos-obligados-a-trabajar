#ifndef SPRITES_H
#define SPRITES_H

#include <string>

struct Sprites
{
   std::string title = 
"\033[38;5;94m"
"  ___                                                                      ___ \n"
" ( _ )--------------------------------------------------------------------( _ )\n"
"  | |                                                                      | | \n"
"  | |                                                                      | | \n"
"\033[1;33m" 
"  | |   ######  ######  ##  ##  #####           ######  ##  ##  ######     | | \n"
"  | |   ##        ##    ### ##  ##  ##            ##    ##  ##  ##         | | \n"
"  | |   ####      ##    ## ###  ##  ##            ##    ######  ####       | | \n"
"  | |   ##        ##    ##  ##  ##  ##            ##    ##  ##  ##         | | \n"
"  | |   ##      ######  ##  ##  #####             ##    ##  ##  ######     | | \n"
"  | |   ................................................................   | | \n"
"  | |   ######  #####   ######   ####    ####    ##  ##  #####   ######    | | \n"
"  | |     ##    ##  ##  ##      ##  ##  ##       ##  ##  ##  ##  ##        | | \n"
"  | |     ##    #####   ####    ######   ####    ##  ##  #####   ####      | | \n"
"  | |     ##    ##  ##  ##      ##  ##      ##   ##  ##  ##  ##  ##        | | \n"
"  | |     ##    ##  ##  ######  ##  ##   ####     ####   ##  ##  ######    | | \n"
"  | |   ................................................................   | | \n"
"\033[38;5;94m"
"  |_|                                                                      |_| \n"
" (___)--------------------------------------------------------------------(___)\n"
"\033[0m";

 std::string menu =
    "\033[97m" "____________________________________ \n"  // Borde blanco
    "|" "\033[0m" "                                    " "\033[97m" "|\n"
    "|" "\033[1;36m" "   **** ENCUENTRA EL TESORO! ****   " "\033[97m" "|\n"
    "|" "\033[97m" "------------------------------------" "|\n"
    "|" "\033[1;36m" "  1. Jugar en modo solitario        " "\033[97m" "|\n"
    "|" "\033[1;35m" "  2. Jugar en modo multijugador     " "\033[97m" "|\n"
    "|" "\033[1;36m" "  3. Cargar partida guardada        " "\033[97m" "|\n"
    "|" "\033[1;32m" "  4. Guardar partida actual         " "\033[97m" "|\n"
    "|" "\033[1;33m" "  5. Mostrar tutorial               " "\033[97m" "|\n"
    "|" "\033[1;33m" "  6. Salir del juego                " "\033[97m" "|\n"
    "|" "\033[97m" "____________________________________|\n"
    "\033[0m" // Reset al final para que no afecte texto siguiente
    "Seleccione una opcion: ";


 std::string menu_action_player =
    "\033[97m" "+-----------------------------------------+\n"  // bordes blancos
    "|" "\033[0m" "           " "\033[1;36m" "Que desea hacer?" "\033[97m" "              |\n"
    "+-----------------------------------------+\n"
    "|" "\033[1;33m" "  1. Excavar                             " "\033[97m" "|\n"
    "|" "\033[1;35m" "  2. Protegerse                          " "\033[97m" "|\n"
    "|" "\033[1;32m" "  3. Disparar con pistola                " "\033[97m" "|\n"
    "|" "\033[1;36m" "  4. Salir y guardar partida             " "\033[97m" "|\n"
    "+-----------------------------------------+\n"
    "\033[0m"
    "Opcion: ";


  std::string dificulty =
    "\033[97m" " _______________________________________\n"  // borde blanco
    "|" "\033[0m" "                                       " "\033[97m" "|\n"
    "|" "\033[1;36m" "         Selecciona dificultad:        " "\033[97m" "|\n"
    "|" "\033[97m" "---------------------------------------" "|\n"
    "|" "\033[1;33m" " 1. Facil   (10x10 - 30 bombas)        " "\033[97m" "|\n"
    "|" "\033[1;35m" " 2. Medio   (20x20 - 80 bombas)        " "\033[97m" "|\n"
    "|" "\033[1;32m" " 3. Dificil (30x30 - 100 bombas)       " "\033[97m" "|\n"
    "|" "\033[97m" "_______________________________________|\n"
    "\033[0m"
"Opcion: )";

   std::string bomb =
       // Brown
       "\033[38;2;139;69;19m"
       R"(         _.-^^---....,,--       
     _--                  --_  
    <                        >)
    |                         | 
     \._                   _./  )"
       // Gray
       "\033[37m"
R"(        ```--. . , ; .--'''       
              | |   |             
           .-=||  | |=-.   
           `-=#$%&%$#=-'   )"
       // yellow
       "\033[1;33m"
       R"(              | ;  :|     
     _____.,-#%&$@%#&#~,._____)"
       "\033[0m";

   std::string treasure = "\033[96m"
                          R"(
       /\
      /  \
     /    \
    /      \
    \      /
     \    /
      \  /
       \/
)"
                          "\033[0m"; // light blue

   std::string shield = "\033[94m"
                        R"(
       _,--`--,_
     ,'    _    `.
    /    _/ \_    \
   |    /     \    |
   |   |       |   |
   |   |       |   |
    \   \     /   /
     `.  `---'  ,'
       `-.____.-'
)"
                        "\033[0m"; // blue
   std::string pistol =
       R"(
        _______ 
       /       \__________________________________
      /        |                                 |
     |_________|                                 |
     |   |     |                                 |
     |   |     |=======>                         |
     |___|_____|_________________________________|
        |     |
        |_____|
    )";

   std::string gameOver = R"(
   __________________________
  /                         /
 /        GAME OVER        /
/_________________________/
)";

   std::string winner = "\033[1;33m"
                        R"(
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
)"
                        "\033[0m"; // bright yellow

   std::string explosion =
       "\033[1;31m"
       R"(       
       .-^---.
     .'       `.
    /           \
   |   BOOM!     |
    \           /
     `.       .'
       `-...-'
)"
       "\033[0m";
 std::string tutorial =
    "\033[96m ________________________________________________________________________________________________________________________________________ \033[0m\n"
    "\033[96m|\033[0m                                                                                                                                        \033[96m|\033[0m\n"
    "\033[96m|\033[0m                                                                TUTORIAL DE JUEGO                                                       \033[96m|\033[0m\n"
    "\033[96m|----------------------------------------------------------------------------------------------------------------------------------------|\033[0m\n"
    "\033[96m|\033[0m  1. Selecciona el modo en el que deseas jugar(solitario o multijugador).                                                               \033[96m|\033[0m\n"
    "\033[96m|\033[0m  2. Selecciona la dificultad que deseas jugar(Facil, Normal,  Dificil).                                                                \033[96m|\033[0m\n"
    "\033[96m|\033[0m  3. Dependiendo la dificultad escogida se otorgará al jugador una cantidad de escudos y balas para la pistola.                         \033[96m|\033[0m\n"
    "\033[96m|\033[0m  4. Ingresa tu nombre de usuario(Sin espacios).                                                                                         \033[96m|\033[0m\n"
    "\033[96m|\033[0m  5. Ingresa el numero de fila que desea seleccionar(que esté dentro de los parámetros).                                                \033[96m|\033[0m\n"
    "\033[96m|\033[0m  6. Ingrese el numero de columna que desea seleccionar(que esté dentro de los parámetros).                                             \033[96m|\033[0m\n"
    "\033[96m|\033[0m  7. Se le darán 4 opciones (1=excavar, 2=protegerse, 3=disparar con pistola, 4=Guardar y salir).                                       \033[96m|\033[0m\n"
    "\033[96m|\033[0m    7.1 \"1=excavar\": Le permite abrir una celda que no se ha marcado aún con la probabilidad que salga un tesoro o una bomba.            \033[96m|\033[0m\n"
    "\033[96m|\033[0m    7.2 \"2=protegerse\": Usa uno de los escudos asignados para evitar perder si pisa una bomba (se pierde lo use o no).                   \033[96m|\033[0m\n"
    "\033[96m|\033[0m    7.3 \"3=disparar con pistola\": Usa una bala asignada para ganar puntos extra si acierta a una bomba (si falla, pierde la bala).      \033[96m|\033[0m\n"
    "\033[96m|\033[0m  8. \"4=Guardar y salir\": Deja la partida hasta donde se ha llegado, con todos los datos guardados, y se retira del juego.              \033[96m|\033[0m\n"
    "\033[96m|\033[0m  9. El objetivo del juego es evitar todas las bombas en el tablero y conseguir la mayor cantidad de puntos.                          \033[96m|\033[0m\n"
    "\033[96m|________________________________________________________________________________________________________________________________________|\033[0m\n";

};

extern Sprites sprites;

#endif
