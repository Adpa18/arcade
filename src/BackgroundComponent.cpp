/*
** BackgroundComponent.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:17 2016 Nicolas Constanty
** Last update	Thu Mar 17 00:33:18 2016 Adrien WERY
*/

#include "BackgroundComponent.hpp"

BackgroundComponent::BackgroundComponent(ComponentColor color, std::string const &sprite2D)
    : AComponent(Vector2(0, 0), color)
{
  this->sprite2D = sprite2D;
}

BackgroundComponent::~BackgroundComponent()
{}

std::string const &BackgroundComponent::getSprite2D() const
{
  return (this->sprite2D);
}

void              BackgroundComponent::setSprite2D(const std::string &sprite2D)
{
    this->sprite2D = sprite2D;
}
