/*
** vector2.hpp for
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:07:00 2016 Nicolas Constanty
** Last update	Tue Mar 08 17:23:35 2016 Nicolas Constanty
*/

#include "Vector2.hpp"

Vector2::Vector2(size_t x, size_t y)
{
  this->x = x;
  this->y = y;
}

Vector2::~Vector2()
{}

Vector2::Vector2(const Vector2 &obj)
{
  *this = obj;
}

Vector2 &Vector2::operator=(const Vector2 &vec)
{
  this->x = vec.x;
  this->y = vec.y;
  return *this;
}
