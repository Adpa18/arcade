/*
** UIComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:40:56 2016 Nicolas Constanty
** Last update	Tue Mar 15 19:24:47 2016 Adrien WERY
*/

#include "UIComponent.hpp"

UIComponent::UIComponent(Vector2 const &p, ComponentColor color,
        Vector2 const &d, std::string const &s)
 : AComponent(p, color), dim(d)
{
  this->text = s;
}

UIComponent::~UIComponent()
{}

Vector2 const &UIComponent::getDim() const
{
  return (this->dim);
}

std::string const &UIComponent::getString() const
{
  return (this->text);
}
