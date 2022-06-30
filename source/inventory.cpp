/*
** EPITECH PROJECT, 2021
** Step1Help
** File description:
** inventaire.cpp
*/

#include "inventory.hpp"

Inventory::Inventory()
{
    std::ifstream myfile("../ressources/block.json");
    std::stringstream ss;
    std::string buff;
    myfile >> brut;

    for (json::iterator start = brut.begin(); start != brut.end(); start++) {
        ss.str(std::string());
        ss << (*start)["sprite"];
        buff = ss.str();
        buff = std::regex_replace(buff, std::regex("\""), "");
        sprite.push_back(LoadImage(buff.c_str()));
    }
    myfile.close();
}