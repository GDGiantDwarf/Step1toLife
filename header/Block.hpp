/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Block
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "raylib.h"

typedef enum {
    AIR = 0,
    STONE,
    DIRT,
    GRASS,
    COBBLE,
    VOID
} BlockType;

class Block {
    public:
        Block(BlockType type);
        void hit(int strenght);
        void Draw(Vector3 position, Model *model);
        Color darken(Color base, float y);
        char letter();
        void Destroy();
        void Create(BlockType type);
        ~Block();
        BlockType type;
        BoundingBox boundingBox;
    protected:
    private:
        Color color;
        bool hasbox = false;
        float destroy_timer;
        float toughness;
};

#endif /* !BLOCK_HPP_ */
