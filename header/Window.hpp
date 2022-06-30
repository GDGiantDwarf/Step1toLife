/*
** EPITECH PROJECT, 2022
** Step1toLife
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "raylib.h"

class Window {
    public:
        Window(int width, int height, int fps);
        void initWindow();
        bool isWindowClosed();
        void begin();
        void begin3D(Camera camera);
        void end3D();
        void end();
        void close();
        ~Window();
    private:
        int width;
        int height;
        int fps;
};

#endif /* !WINDOW_HPP_ */
