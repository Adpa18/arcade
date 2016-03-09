/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Wed Mar 09 16:07:57 2016 Nicolas Constanty
*/

#include "AComponent.hpp"

AComponent::AComponent(Vector2 p) : pos(p)
{}

AComponent::AComponent(size_t x, size_t y) : pos(Vector2(x, y))
{}

AComponent::~AComponent ()
{}

Vector2 const &AComponent::getPos() const
{
  return (this->pos);
}
