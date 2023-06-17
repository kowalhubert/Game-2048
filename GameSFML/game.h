#ifndef GAMESFML_GAME_H
#define GAMESFML_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

constexpr int boardSize = 4,
        TITLESIZE = 64,
        WIDTH = boardSize*TITLESIZE,
        HEIGHT = boardSize*TITLESIZE;

bool g_win;
int MAP[boardSize][boardSize];

enum class Direction{
    Left,
    Right,
    Up,
    Down,
};

sf::Vector2i genPos();
int genNewTitle();
void placeNewTitle();
void shift(Direction d);
void welcome();
void cleanBoard();
void runGame();
void winOrLoseWindow(int a);
bool checkLose();

#endif //GAMESFML_GAME_H
