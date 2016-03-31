#include "AGame.hpp"

AGame::AGame(std::string const &name) : state(ALIVE), name(name),
    size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
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
