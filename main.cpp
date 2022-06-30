/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** main
*/

#include "Game.hpp"
#include "menu.hpp"

int main (void)
{
    Game game;
    Menu menu_princ;

    std::srand(std::time(nullptr));
    menu_princ.init_menu(&game);
    menu_princ.start_menu(game);
    // game->loop();
    return 0;
}