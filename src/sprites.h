#ifndef SPRITES_H
#define SPRITES_H

#include <string>

struct Sprites
{
    std::string title;
    std::string menu;
    std::string dificulty;
    std::string bomb;
    std::string treasure;
    std::string shield;
    std::string pistol;
    std::string gameOver;
    std::string winner;
    std::string explosion;
};

extern Sprites sprites;

#endif
