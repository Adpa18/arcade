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
