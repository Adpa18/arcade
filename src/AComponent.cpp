/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Wed Mar 16 10:34:05 2016 Adrien WERY
*/

#include "AComponent.hpp"

AComponent::AComponent(Vector2 const &p, ComponentColor color) : pos(p), size(Vector2(0, 0)), color(color)
{}

AComponent::AComponent(Vector2 const &p, Vector2 const &s, ComponentColor color) : pos(p), size(s), color(color)
{}

AComponent::AComponent(int x, int y, ComponentColor color) : pos(Vector2(x, y)), size(Vector2(0, 0)), color(color)
{}

AComponent::~AComponent ()
{}

Vector2 const &AComponent::getPos() const
{
  return (this->pos);
}

void            AComponent::setPos(const Vector2 &pos)
{
    this->pos = pos;
}

Vector2 const   &AComponent::getSize() const
{
  return (this->size);
};

void            AComponent::setSize(const Vector2 &size)
{
    this->size = size;
}

ComponentColor const   &AComponent::getColor() const
{
    return this->color;
}

void            AComponent::setColor(const ComponentColor color)
{
    this->color = color;
}
