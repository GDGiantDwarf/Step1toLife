/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "raylib.h"
#include "fastnoiselite.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <map>

#include "inventory.hpp"
#include "Window.hpp"
#include "Inputs.hpp"
#include "Chunkmap.hpp"
#include "rlFPCamera.hpp"
#define PAIR_X first
#define PAIR_Y second

using json = nlohmann::json;

typedef struct
{
    int chunk_x;
    int chunk_y;
    int block_i;
    int block_j;
    int block_k;
    float distance;
    Vector3 colNorm;
} RayColData;

class Game {
    public:
        Game();
        void init();
        void events();
        void loop();
        void draw();
        void tryput();
        void trybreak();
        void drawHUD();
        std::string heldstr(BlockType block);
        ~Game();
        Window *window;
    private:
        int inv[6] = {0, 20, 20, 20, 20, 0};
        BlockType held;
        bool showHUD;
        int seed;
        Ray sight;
        Vector2 mouseMovement;
        Chunkmap *chunkmap;
        rlFPCamera cam;
        Inputs *inputs;
        Inventory inventory;
};

void quit_game(Game &game);
void launch_game(Game &game);

#endif /* !GAME_HPP_ */
