/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Mon Mar 28 21:17:39 2016 Nicolas Constanty
*/

#include "AComponent.hpp"

AComponent::AComponent(Vector2<int> const &p, ComponentColor color) : pos(p), size(Vector2<int>(0, 0)), color(color)
{}

AComponent::AComponent(Vector2<int> const &p, Vector2<int> const &s, ComponentColor color) : pos(p), size(s), color(color)
{}

AComponent::AComponent(int x, int y, ComponentColor color) : pos(Vector2<int>(x, y)), size(Vector2<int>(0, 0)), color(color)
{}

AComponent::~AComponent ()
{}

Vector2<int> const &AComponent::getPos() const
{
  return (this->pos);
}

void            AComponent::setPos(const Vector2<int> &pos)
{
    this->pos = pos;
}

Vector2<int> const   &AComponent::getSize() const
{
  return (this->size);
};

void            AComponent::setSize(const Vector2<int> &size)
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
