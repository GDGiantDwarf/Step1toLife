/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Chunkmap
*/

#ifndef CHUNKMAP_HPP_
#define CHUNKMAP_HPP_

#include "raylib.h"
#include "fastnoiselite.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <map>

#include "Chunk.hpp"

class Chunkmap {
    public:
        Chunkmap(int seed);
        void GenChunk(int x, int y);
        Chunk *GetChunk(int x, int y);
        void FillNoise(Chunk *chunk);
        void CheckLoading(int x, int y);
        void UnloadCheck(int x, int y);
        void LoadCheck(int x, int y);
        void debugChunkPrint(int x, int y);
        void Draw();
        ~Chunkmap();
        bool meshLoaded = false;
        Mesh cubemesh = {0};
        Model cubemodel;
    private:
        FastNoiseLite *FNL;
        std::map<std::pair<int, int>, Chunk*> map;
        int load_distance = 2;
        int debug_max_x = 0;
        int debug_max_y = 0;
        int debug_min_x = 0;
        int debug_min_y = 0;
};

#endif /* !CHUNKMAP_HPP_ */
