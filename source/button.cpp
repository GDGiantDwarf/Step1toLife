/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** button.cpp
*/

#include "button.hpp"

button_class::button_class()
{
    std::cout << "********************************" << std::endl;
    std::cout << "init screen size" << std::endl;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    std::cout << "init variables" << std::endl;
    btnState = 0;
    btnAction = false;
    mousePoint = {0.0f, 0.0f};
    std::cout << "********************************" << std::endl;
}

button_class button_class::make_button(int nbr_frame, std::string path, Vector2 pos, void (*functi)(Game &game), Game *game_i)
{
    std::cout << "********************************" << std::endl;
    std::cout << "load button texture" << std::endl;
    button = LoadTexture(path.c_str());
    std::cout << "init size rec" << std::endl;
    frameHeight = (float)button.height / nbr_frame;
    sourceRec = {0, 0, (float)button.width, frameHeight};
    std::cout << "bind button" << std::endl;
    btnBounds = {pos.x - button.width / 2.0f, pos.y - button.height / nbr_frame / 2.0f, (float)button.width, frameHeight};
    std::cout << "bind function" << std::endl;
    funct = functi;
    game = game_i;
    std::cout << "********************************" << std::endl;
    return (*this);
}

void button_class::draw_button()
{
    mousePoint = GetMousePosition();
    btnAction = false;
    if (CheckCollisionPointRec(mousePoint, btnBounds))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else
        btnState = 0;
    if (btnAction)
    {
        this->funct(*this->game);
        if (this->game->window->isWindowClosed())
            return;
    }
    sourceRec.y = btnState * frameHeight;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTextureRec(button, sourceRec, {btnBounds.x, btnBounds.y}, WHITE);
}

void button_class::unload_button()
{
    std::cout << "********************************" << std::endl;
    try {
        std::cout << "Unloading button texture" << std::endl;
        UnloadTexture(button);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    std::cout << "********************************" << std::endl;
}