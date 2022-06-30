/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** inventaire.hpp
*/

#ifndef __inventaire_H__
    #define __inventaire_H__

    #include "raylib.h"
    #include <algorithm>
    #include <regex>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <iterator>
    #include <array>
    #include <nlohmann/json.hpp>
    using json = nlohmann::json;

class Inventory
{
    public:
        json brut;
        std::vector<Image> sprite;
        Inventory();
    private:
};

#endif