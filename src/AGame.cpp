/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Fri Mar 11 18:20:17 2016 Adrien WERY
*/

#include "AGame.hpp"

AGame::AGame(std::string const &name, Vector2 size) : name(name), size(size)
{

}

AGame::~AGame()
{

}

Vector2 const           &AGame::getSize() const
{
    return (this->size);
}

std::string const       &AGame::getName() const
{
    return (this->name);
}
