/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Block
*/

#include "Block.hpp"
#include <iostream>

Block::Block(BlockType newtype)
{
    switch (newtype)
    {
    case AIR:
        this->color = BLANK;
        break;
    case STONE:
        this->color = GRAY;
        break;
    case DIRT:
        this->color = BROWN;
        break;
    case GRASS:
        this->color = GREEN;
        break;
    case COBBLE:
        this->color = BEIGE;
    default:
        break;
    }
    this->type = newtype;
}

Color Block::darken(Color color, float height)
{
    float mul = 0.0f;
    for (int i = 0; i < height; i++, mul += 0.05);

    color.r *= mul;
    color.g *= mul;
    color.b *= mul;
    return color;
}

char Block::letter()
{
    switch (this->type)
        {
        case AIR:
            return 'A';
        case STONE:
            return 'S';
        case DIRT:
            return 'D';
        case GRASS:
            return 'G';
        case COBBLE:
            return 'C';
        default:
            return '\0';
        }
}

static Vector3 getPos(float x, float y, float z)
{
    Vector3 vec = {};
    vec.x = x;
    vec.y = y;
    vec.z = z;

    return (vec);
}

void Block::Draw(Vector3 position, Model *model)
{
    Model x = *model;
    if (!this->hasbox) {
        this->boundingBox = GetModelBoundingBox(*model);
        this->boundingBox.max = getPos(position.x + 0.5f, position.y +0.5f, position.z +0.5f);
        this->boundingBox.min = getPos(position.x - 0.5f, position.y -0.5f, position.z -0.5f);
        this->hasbox = true;
    }
    if(this->type != AIR) {
        DrawModel(x, position, 1.0f, this->darken(this->color, position.y));
        DrawBoundingBox(this->boundingBox, BLACK);
    }
}

void Block::Destroy()
{
    this->type = AIR;
    this->color = BLANK;
}

void Block::Create(BlockType type)
{
    this->type = type;
    switch (type)
    {
    case AIR:
        this->color = BLANK;
        break;
    case STONE:
        this->color = GRAY;
        break;
    case DIRT:
        this->color = BROWN;
        break;
    case GRASS:
        this->color = GREEN;
        break;
    case COBBLE:
        this->color = BEIGE;
    default:
        break;
    }
    
}

Block::~Block()
{
}
