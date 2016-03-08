/*
** ObjectTerm.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:26:18 2016 Nicolas Constanty
** Last update	Tue Mar 08 17:37:17 2016 Nicolas Constanty
*/

#include "ObjectTerm.hpp"


ObjectTerm::ObjectTerm(char c, Vector2 const &coord, Vector2 const &dim)
 : Object(coord, dim)
{
  this->carac = c;
}

ObjectTerm::~ObjectTerm ()
{}

char ObjectTerm::getCaract() const
{
  return (this->carac);
}
