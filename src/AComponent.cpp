#include "AComponent.hpp"

AComponent::AComponent(int x, int y, ComponentColor c) : pos(Vector2<double>(x, y)), _color(c)
{}

AComponent::AComponent(Vector2<double> const &p, ComponentColor c) : pos(p), _color(c)
{}

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

AComponent::ComponentColor   AComponent::getColor() const
{
    return this->_color;
}

void            AComponent::setColor(ComponentColor color)
{
    this->_color = color;
}
