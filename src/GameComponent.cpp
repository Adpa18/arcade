/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:55:29 2016 Nicolas Constanty
** Last update	Tue Mar 15 23:37:49 2016 Adrien WERY
*/

#include "GameComponent.hpp"

GameComponent::GameComponent(Vector2 const &p, Vector2 const &s, ComponentColor color,
    std::string const &spriteText, std::string const &sprite2D, void *sprite3D)
     : AComponent(p, s, color)
{
  this->spriteText = spriteText;
  this->sprite2D = sprite2D;
  this->sprite3D = sprite3D;
}

GameComponent::~GameComponent()
{}

std::string const &GameComponent::getSpriteText() const
{
  return (this->spriteText);
}

std::string const &GameComponent::getSprite2D() const
{
  return (this->sprite2D);
}

void *GameComponent::getSprite3D() const
{
  return (this->sprite3D);
}

void              GameComponent::setSpriteText(const std::string &spriteText)
{
    this->spriteText = spriteText;
}

void              GameComponent::setSprite2D(const std::string &sprite2D)
{
    this->sprite2D = sprite2D;
}

void              GameComponent::setSprite3D(void *sprite3D)
{
    this->sprite3D = sprite3D;
}
