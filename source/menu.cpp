/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** menu.cpp
*/

#include "menu.hpp"

Menu::Menu()
{
}

void Menu::init_menu(Game *game)
{
    button_class button_base;
    button_all.push_back(button_base.make_button(3, "../ressources/start_button.png", {400, 225}, launch_game, game));
    button_all.push_back(button_base.make_button(3, "../ressources/quit_button.png", {400/4, 225/4}, quit_game, game));
}

void Menu::start_menu(Game &game)
{
    while (!game.window->isWindowClosed())
    {
        for (auto button = button_all.begin(); button != button_all.end(); button++) {
            button->draw_button();
            if (game.window->isWindowClosed()) {
                break;
            }
        }
        if (game.window->isWindowClosed()) {
            break;
        }
        if (WindowShouldClose()) {
            CloseWindow();
        }
        EndDrawing();
    }

    // for (auto button = button_all.begin(); button != button_all.end(); button++)
    //     button->unload_button();
    // UnloadTexture(this->button); // Unload button texture
    CloseAudioDevice();    // Close audio device
}