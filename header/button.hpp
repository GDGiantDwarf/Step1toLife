/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** button.hpp
*/

#ifndef __button_H__
    #define __button_H__

    #include "Game.hpp"

    class button_class
    {
    private:
        int screenWidth;
        int screenHeight;
        float frameHeight;
        Rectangle sourceRec;
        Rectangle btnBounds;
        int btnState;
        bool btnAction;
        Vector2 mousePoint;
        Texture2D button;
        void (*funct)(Game &game);
        Game *game;

    public:
        button_class();
        button_class make_button(int, std::string, Vector2, void (*funct)(Game &), Game *);
        void draw_button();
        void unload_button();
    };
#endif