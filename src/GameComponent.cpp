/*
** GameComponent.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:17 2016 Nicolas Constanty
** Last update	Wed Mar 30 17:27:29 2016 Nicolas Constanty
*/

#include "GameComponent.hpp"

GameComponent::GameComponent(Vector2<double> const &pos,
			     AComponent::ComponentColor color,
			     Shapes sprite3D,
			     std::string const &spriteText,
                             std::string const &sprite2D)
  : AComponent(pos, color), sprite3D(sprite3D),
    spriteText(spriteText), fileSprite2D(sprite2D)
{
}

GameComponent::GameComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color,
    char const &spriteText, std::string const &sprite2D, Shapes sprite3D)
     : AComponent(p, color), dim(s)
{
  this->spriteText = spriteText;
  this->fileSprite2D = sprite2D;
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
  return (this->fileSprite2D);
}

GameComponent::Shapes GameComponent::getSprite3D() const
{
  return (this->sprite3D);
}

void              GameComponent::setSpriteText(const char &spriteText)
{
    this->spriteText = spriteText;
}

void              GameComponent::setSpriteText(const std::string &spriteText)
{
    this->spriteText = spriteText;
}

void              GameComponent::setSprite2D(const std::string &sprite2D)
{
    this->fileSprite2D = sprite2D;
}

void              GameComponent::setSprite3D(Shapes sprite3D)
{
    this->sprite3D = sprite3D;
}

Vector2<double> const &GameComponent::getDim() const
{
  return this->dim;
}
