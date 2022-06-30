/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Chunkmap
*/

#include "Chunkmap.hpp"

namespace ChunkFunc
{
    bool IsIn(std::pair<int, int> chunk, std::pair<int, int> center, int range)
    {
        if (chunk.first < (center.first - range) || chunk.first > (center.first + range))
            return false;
        if (chunk.second < (center.second - range) || chunk.second > (center.second + range))
            return false;
        return true;
    }
};

Chunkmap::Chunkmap(int seed)
{
    this->FNL = new FastNoiseLite();
    this->FNL->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    this->FNL->SetSeed(seed);
}

void Chunkmap::GenChunk(int x, int y)
{
    Chunk *chunk = new Chunk(x, y);
    //check for files
    this->FillNoise(chunk);
    chunk->Gen();
    std::pair<int, int> coords = std::make_pair(x, y);
    std::pair<std::pair<int, int>, Chunk *> pair = std::make_pair(coords, chunk);
    this->map.insert(pair);

    //for debug
    this->debug_max_x  = std::max(this->debug_max_x, x);
    this->debug_max_y  = std::max(this->debug_max_y, y);
    this->debug_min_x  = std::min(this->debug_min_x, x);
    this->debug_min_y  = std::min(this->debug_min_y, y);
}

void Chunkmap::FillNoise(Chunk *chunk)
{
    float noiseVal = 0.0f;
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            noiseVal = this->FNL->GetNoise((float)(chunk->chunk_x * 16 + x), (float)((chunk->chunk_y * 16 + y)));
            chunk->noise[x][y] = (int) std::round(noiseVal * 5) + 10;
        }
    }
    // std::cout << "Generating noise for chunk" << chunk->chunk_x << ", " << chunk->chunk_y << std::endl;
    // for (int i = 0; i < 16; ++i)
    // {
    //     for (int j = 0; j < 16; ++j)
    //     {
    //         std::cout << chunk->noise[i][j] << ' ';
    //     }
    //     std::cout << std::endl;
    // }
}

Chunk *Chunkmap::GetChunk(int x, int y)
{
    std::pair<int, int> coords = std::make_pair(x, y);
    if (this->map.count(coords) == 0)
        GenChunk(x, y);
    return this->map[coords];
}

void Chunkmap::CheckLoading(int x, int y)
{
    int chunk_x = std::floor((float)x/16);
    int chunk_y = std::floor((float)y/16);

    if(!this->meshLoaded) {
        this->cubemesh = GenMeshCube(1.0f, 1.0f, 1.0f);
        this->cubemodel = LoadModelFromMesh(this->cubemesh);
        this->meshLoaded = true;
    }

    this->UnloadCheck(chunk_x, chunk_y);
    this->LoadCheck(chunk_x, chunk_y);
}

void Chunkmap::LoadCheck(int x, int y)
{
    std::pair<int, int> coords;
    for (int i = (x - this->load_distance); i <= (x + this->load_distance); i++)
        for (int j = (y - this->load_distance); j <= (y + this->load_distance); j++)
            GetChunk(i, j);
}

void Chunkmap::UnloadCheck(int x, int y)
{
    std::pair<int, int> coords = std::make_pair(x, y);
    for (auto it = std::begin(this->map); it != std::end(this->map);)
    {
        if (!(ChunkFunc::IsIn(it->first, coords, this->load_distance))) {
            it->second->save();
            std::cout << "Unloaded chunk " << it->first.first << ", " << it->first.second << std::endl;
            delete it->second;
            it = this->map.erase(it);
        }
        else
            it++;
    }
}

void Chunkmap::debugChunkPrint(int x, int y)
{
    std::pair<int, int> coords;
    std::cout << "xmin : " << this->debug_min_x << std::endl;
    std::cout << "xmax : " << this->debug_max_x << std::endl;
    std::cout << "ymin : " << this->debug_min_y << std::endl;
    std::cout << "ymax : " << this->debug_max_y << std::endl;
    for(int i = -2; i <= (this->debug_max_x - this->debug_min_x); i++)
        std::cout <<"_";
    std::cout << std::endl;

    for(int i = this->debug_min_x; i <= this->debug_max_x; i++) {
        std::cout << "|";
        for(int j = this->debug_min_y; j <= this->debug_max_y; j++ ){
            coords = std::make_pair(i, j);
            if (this->map.count(coords) == 0)
                std::cout << " ";

            else if (coords == std::make_pair(x, y))
                std::cout << "P";
            else
                std::cout << this->map.count(coords);
        }
        std::cout <<"|"<<std::endl;
    }

    for(int i = -2; i <= (this->debug_max_x - this->debug_min_x); i++)
        std::cout <<"-";
    std::cout << std::endl << std::endl;
}

void Chunkmap::Draw()
{
    for (auto it = std::begin(this->map); it != std::end(this->map); it++)
    {
        it->second->Draw(&(this->cubemodel));
    }
}

Chunkmap::~Chunkmap()
{
}
