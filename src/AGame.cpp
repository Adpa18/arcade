/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Mon Mar 28 21:26:39 2016 Nicolas Constanty
*/

#include "AGame.hpp"

AGame::AGame(std::string const &name, Vector2<double> size) : name(name), size(size)
{

}

AGame::~AGame()
{

}

Vector2<double> const           &AGame::getSize() const
{
    return (this->size);
}

std::string const       &AGame::getName() const
{
    return (this->name);
}
