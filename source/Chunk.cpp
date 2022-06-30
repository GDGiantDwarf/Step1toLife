/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Chunk
*/

#include "Chunk.hpp"
#include <iostream>

Chunk::Chunk(int x, int y)
{
    this->chunk_x = x;
    this->chunk_y = y;
}

void Chunk::Gen()
{
    int height;
    if(!this->existfile())
    for (int i = 0; i <16; i++)
        for (int j = 0; j <16; j++) {
            for (height = 0; height < this->noise[i][j] - 4; height++)
                this->blockmap[i][j][height] = new Block(STONE);
            for (; height < this->noise[i][j] - 1; height++)
                this->blockmap[i][j][height] = new Block(DIRT);
            for (; height < this->noise[i][j]; height++)
                this->blockmap[i][j][height] = new Block(GRASS);
            for (; height < 20; height++)
                this->blockmap[i][j][height] = new Block(AIR);
        }
}

bool Chunk::existfile()
{
    struct stat buffer;
    std::stringstream ss;
    ss << SAVEFILEPATH << this->chunk_x << "_" << this->chunk_y << ".json";
    std::string name = ss.str();
    if(!(stat (name.c_str(), &buffer) == 0))
        return false;
    std::cout << name << " FOUND" << std::endl;
    this->fillFromFile(name);
    return false; //should return true
}

void Chunk::fillFromFile(std::string name)
{

}

static Vector3 getPos(float x, float y, float z)
{
    Vector3 vec = {};
    vec.x = x;
    vec.y = y;
    vec.z = z;

    return (vec);
}

void Chunk::Draw(Model *model)
{
    for(int height = 0; height < 20; height++)
        for(int i = 0; i <16; i++)
            for(int j = 0; j <16; j++)
            this->DrawAt(i, j, height, model);
}

void Chunk::DrawAt(int i, int j, int height, Model *model)
{
    Vector3 position = getPos((float)this->chunk_x * 16 + i, height, (float)this->chunk_y * 16 + j);
    this->blockmap[i][j][height]->Draw(position, model);
}

void Chunk::save()
{
    std::stringstream ss;
    std::stringstream buff;
    std::ofstream file;
    json jason;
    std::cout << "call" << std::endl;

    ss << "../save/chunks/" << this->chunk_x << "_" << this->chunk_y << ".json";
    file.open(ss.str());
    for (int i = 0; i <16; i++)
        for (int j = 0; j <16; j++) {
            ss.str(std::string());
            buff.str(std::string());
            ss << i << "_" << j;
            for (int x =0; x < 20; x++) {
                buff << this->blockmap[i][j][x]->letter();
            }
            jason[ss.str().c_str()] = buff.str().c_str();
        }
    file << jason.dump(4);
    file.close();
}

Chunk::~Chunk()
{
    for (int i = 0; i <16; i++)
        for (int j = 0; j <16; j++) {
            for (int k = 0; k < 20; k++)
                delete this->blockmap[i][j][k];
        }
}