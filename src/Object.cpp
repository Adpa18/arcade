/*
** Object.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:16:49 2016 Nicolas Constanty
** Last update	Tue Mar 08 17:25:48 2016 Nicolas Constanty
*/

#include "Object.hpp"


Object::Object(Vector2 const &newCoord, Vector2 const &newDim)
 : coord(newCoord), dim(newDim)
{}

Object::~Object()
{}

Vector2 const &Object::getCoord() const
{
  return (this->coord);
}

Vector2 const &Object::getDim() const
{
  return (this->dim);
}
