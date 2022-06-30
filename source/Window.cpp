/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** Window
*/

#include "Window.hpp"

Window::Window(int width, int height, int fps)
{
    this->width = width;
    this->height = height;
    this->fps = fps;
}

void Window::initWindow()
{
    InitWindow(this->width, this->height, "Bomberman");
    SetTargetFPS(this->fps);
}

bool Window::isWindowClosed()
{
    return (WindowShouldClose());
}

void Window::close()
{
    CloseWindow();
}

void Window::begin()
{
    BeginDrawing();
    ClearBackground(WHITE);
}

void Window::begin3D(Camera camera)
{
    BeginMode3D(camera);
}

void Window::end3D()
{
    EndMode3D();
}

void Window::end()
{
    EndDrawing();
}

Window::~Window()
{
}
