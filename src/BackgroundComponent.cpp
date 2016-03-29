/*
** BackgroundComponent.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:17 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:28:04 2016 Nicolas Constanty
*/

#include "BackgroundComponent.hpp"

BackgroundComponent::BackgroundComponent(Vector2<double> pos, Vector2<double> size, ComponentColor color, std::string const &sprite2D)
    : AComponent(pos, color), dim(size)
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

Vector2<double> const &BackgroundComponent::getDim() const
{
  return this->dim;
}
