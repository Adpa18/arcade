/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 15 15:34:23 2016 Adrien WERY
*/

#include "AComponent.hpp"

AComponent::AComponent(Vector2 const &p) : pos(p)
{}

AComponent::AComponent(int x, int y) : pos(Vector2(x, y))
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
