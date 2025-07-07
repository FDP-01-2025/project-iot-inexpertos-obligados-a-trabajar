#ifndef SPRITES_H
#define SPRITES_H

#include <string>

struct Sprites
{
   std::string title = R"(
  ___                                                                      ___ 
 ( _ )--------------------------------------------------------------------( _ )
  | |                                                                      | | 
  | |                                                                      | | 
  | |   ######  ######  ##  ##  #####           ######  ##  ##  ######     | | 
  | |   ##        ##    ### ##  ##  ##            ##    ##  ##  ##         | | 
  | |   ####      ##    ## ###  ##  ##            ##    ######  ####       | | 
  | |   ##        ##    ##  ##  ##  ##            ##    ##  ##  ##         | | 
  | |   ##      ######  ##  ##  #####             ##    ##  ##  ######     | | 
  | |   ................................................................   | | 
  | |   ######  #####   ######   ####    ####    ##  ##  #####   ######    | | 
  | |     ##    ##  ##  ##      ##  ##  ##       ##  ##  ##  ##  ##        | | 
  | |     ##    #####   ####    ######   ####    ##  ##  #####   ####      | | 
  | |     ##    ##  ##  ##      ##  ##      ##   ##  ##  ##  ##  ##        | | 
  | |     ##    ##  ##  ######  ##  ##   ####     ####   ##  ##  ######    | | 
  | |   ................................................................   | | 
  |_|                                                                      |_| 
 (___)--------------------------------------------------------------------(___)
    )";

   std::string menu = R"(
 ____________________________________ 
|                                    |
|   **** ENCUENTRA EL TESORO! ****   |
|------------------------------------|
|  1. Jugar en modo solitario        |
|  2. Jugar en modo multijugador     |
|  3. Cargar partida guardada        |
|  4. Guardar partida actual         |
|  5. Salir del juego                |
|____________________________________|
Seleccione una opcion: )";

   std::string menu_action_player = R"(
+-----------------------------------------+
|           Que desea hacer?              |
+-----------------------------------------+
|  1. Excavar                             |
|  2. Protegerse                          |
|  3. Disparar con pistola                |
|  4. Salir y guardar partida             |
+-----------------------------------------+
Opcion: )";

   std::string dificulty = R"(
 _______________________________________
|                                       |
|         Selecciona dificultad:        |
|---------------------------------------|
| 1. Facil   (10x10 - 30 bombas)        |
| 2. Medio   (20x20 - 80 bombas)        |
| 3. Dificil (30x30 - 100 bombas)       |
|_______________________________________|
Opcion: )";

   std::string bomb = R"(
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
        )";

   std::string treasure = R"(
       /\
      /  \
     /    \
    /      \
    \      /
     \    /
      \  /
       \/
    )";

   std::string shield = R"(
       _,--`--,_
     ,'    _    `.
    /    _/ \_    \
   |    /     \    |
   |   |       |   |
   |   |       |   |
    \   \     /   /
     `.  `---'  ,'
       `-.____.-'
        )";

   std::string pistol = R"(
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

   std::string winner = R"(
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
    )";

   std::string explosion = R"(
       .-^---.
     .'       `.
    /           \
   |   BOOM!     |
    \           /
     `.       .'
       `-...-'
)";
   std::string tutorial = R"(
 ________________________________________________________________________________________________________________________________________
|                                                                                                                                        |
|                                                                TUTORIAL DE JUEGO                                                       |
|----------------------------------------------------------------------------------------------------------------------------------------|
|  1. Selecciona el modo en el que deseas jugar(solitario o multijugador).                                                               |
|  2. Selecciona la dificultad que deseas jugar(Facil, Normal,  Dificil).                                                                |
|  3. dependiendo la dificultad escogida se otorgará al jugador una cantidad de escudos y balas para la pistola.                         |
|  4. Ingresa tu nombre de usuario(Sin espacios).                                                                                        |
|  5. Ingresa el numero de fila que desea seleccionar(que este dontro de los parametros).                                                |
|  6. Ingrese el numero de columna que desea seleccionar(que este dentro de los parametros).                                             |
|  7.Se le darán 4 opciones (1=excavar,2=protegerse,3=disparar con pistola, 4=Guardar y salir).                                          |
|    7.1 "1=excavar", Le permite abrir una celda que no se ha marcado aún con la probabilidad que salga un tesoro o una bomba.           |
|    7.2 "2=protegerse" Usa uno de los escudos asignados para evitar perder si pisa una bomba (tome en cuenta en que si usa un escudo,   |
|         este se pierde,independientemente hubiese una bomba o no).                                                                     |
|    7.3 "3=disparar con pistola" Usa una de las balas que se ha asignado para ganar puntos extra si se acierta a una bomba              |
|         (Tome een cuenta en que si falla, no ganará puntos extra y habra perdido una bala).                                            |
|  8."4=Guardar y salir" deja la parida hasta donde se ha llegado, con todos los datos de los escudos y balas y se retira del juego      |
|  9.El objetivo del juego es evitar todas las bombas en el tablero y conseguir la mayor cantidad de puntos                              |
|________________________________________________________________________________________________________________________________________|
)";
};

extern Sprites sprites;

#endif
