/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:55:29 2016 Nicolas Constanty
** Last update	Wed Mar 16 07:22:58 2016 Nicolas Constanty
*/

#include "GameComponent.hpp"

GameComponent::GameComponent(Vector2 const &p, Vector2 const &s, ComponentColor color,
    void *spr3D, char const &sprText, std::string const &sprite2D)
     : AComponent(p, s, color)
{
  this->spriteText = sprText;
  this->fileSprite2D = sprite2D;
  this->sprite3D = spr3D;
}

GameComponent::~GameComponent()
{}

char const &GameComponent::getSpriteText() const
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
