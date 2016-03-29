/*
** GameComponent.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:17 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:26:03 2016 Nicolas Constanty
*/

#include "GameComponent.hpp"

GameComponent::GameComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color,
    char const &spriteText, std::string const &sprite2D, void *sprite3D)
     : AComponent(p, color), dim(s)
{
  this->spriteText = spriteText;
  this->sprite2D = sprite2D;
  this->sprite3D = sprite3D;
}

GameComponent::~GameComponent()
{}

char const &GameComponent::getSpriteText() const
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

void              GameComponent::setSpriteText(const char &spriteText)
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

Vector2<double> const &GameComponent::getDim() const
{
  return this->dim;
}
