/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:59:04 2016 Nicolas Constanty
*/

#include "AComponent.hpp"

AComponent::AComponent(int x, int y, ComponentColor color) : pos(Vector2<double>(x, y)), color(color)
{}

AComponent::AComponent(Vector2<double> const &p, ComponentColor color) : pos(p), color(color)
{}

// AComponent::AComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color) : pos(p), size(s), color(color)
// {}

AComponent::~AComponent ()
{}

Vector2<double> const &AComponent::getPos() const
{
  return (this->pos);
}

void            AComponent::setPos(const Vector2<double> &pos)
{
    this->pos = pos;
}

// Vector2<double> const   &AComponent::getSize() const
// {
//   return (this->size);
// };
//
// void            AComponent::setSize(const Vector2<double> &size)
// {
//     this->size = size;
// }

AComponent::ComponentColor   AComponent::getColor() const
{
    return this->color;
}

void            AComponent::setColor(ComponentColor color)
{
    this->color = color;
}
