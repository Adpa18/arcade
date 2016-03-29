/*
** UIComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Tue Mar 29 21:18:32 2016 Nicolas Constanty
*/

#include "UIComponent.hpp"


UIComponent::UIComponent(Vector2<double> const &p, ComponentColor color, Vector2<double> const &s, const std::string &text)
    : AComponent(p, color), dim(s)
{
    this->text = text;
}

UIComponent::~UIComponent ()
{

}

std::string const  &UIComponent::getText() const
{
    return (this->text);
}

Vector2<double> const &UIComponent::getDim() const
{
  return this->dim;
}
