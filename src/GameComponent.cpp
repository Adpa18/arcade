/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:55:29 2016 Nicolas Constanty
** Last update	Thu Mar 10 15:38:43 2016 Adrien WERY
*/

#include "GameComponent.hpp"

GameComponent::GameComponent(Vector2 const &p, void *spr3D, std::string const &sprText,
   std::string const &sprite2D) : AComponent(p)
{
  this->spriteText = sprText;
  this->fileSprite2D = sprite2D;
  this->sprite3D = spr3D;
}

GameComponent::~GameComponent()
{}

std::string const &GameComponent::getSpriteText() const
{
  return (this->spriteText);
}

std::string const &GameComponent::getSprite2D() const
{
  return (this->fileSprite2D);
}

void *GameComponent::getSprite3D() const
{
  return (this->sprite3D);
}
