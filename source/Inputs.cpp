/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Inputs
*/

#include "Inputs.hpp"

Inputs::Inputs()
{
}

Vector2 Inputs::GetMouse(bool reset)
{
    Vector2 r = GetMousePosition();
    r.x = r.x - GetScreenWidth()/2;
    r.y = r.y - GetScreenHeight()/2;
    if (reset){
        SetMousePosition(GetScreenWidth()/2,GetScreenHeight()/2);
        return r;
    }
    return r;
}

bool Inputs::IsPressed(int key)
{
    return (IsKeyDown(key));
}
Inputs::~Inputs()
{
}
