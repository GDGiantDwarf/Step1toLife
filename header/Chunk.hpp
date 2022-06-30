/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** Chunk
*/

#ifndef CHUNK_HPP_
#define CHUNK_HPP_

#include "Block.hpp"
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define SAVEFILEPATH "../save/chunks/"

class Chunk {
    public:
        Chunk(int x, int y);
        void Gen();
        void Draw(Model *model);
        void DrawAt(int x, int y, int height,  Model *model);
        void save();
        bool existfile();
        void fillFromFile(std::string name);
        ~Chunk();
        int chunk_x = 0;
        int chunk_y = 0;
        int noise[16][16];
        Block *blockmap[16][16][20];
};

#endif /* !CHUNK_HPP_ */
