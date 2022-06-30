/*
** EPITECH PROJECT, 2022
** Step1Help
** File description:
** Inputs
*/

#ifndef INPUTS_HPP_
#define INPUTS_HPP_

#include "raylib.h"

class Inputs {
    public:
        Inputs();
        Vector2 GetMouse(bool shouldReset);
        bool IsPressed(int key);
        ~Inputs();

    protected:
    private:
};

#endif /* !INPUTS_HPP_ */
