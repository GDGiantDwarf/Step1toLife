/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** menu.hpp
*/

#ifndef __menu_H__
    #define __menu_H__

    #include "Game.hpp"
    #include "button.hpp"

    #define GAME_NAME "Step1toLife"
    #define GAME_DEV "GDGiantDwarf"

class Menu
{
    private:
        std::vector<button_class> button_all;

    public:
        Menu();
        void init_menu(Game *game);
        void start_menu(Game &game);
};

#endif

