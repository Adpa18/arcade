/*
** vector2.hpp for
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:07:00 2016 Nicolas Constanty
** Last update	Tue Mar 15 19:43:02 2016 Adrien WERY
*/

#include "Vector2.hpp"

Vector2::Vector2(int x, int y)
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

bool    Vector2::operator==(const Vector2 &vec) const
{
    return (this->x == vec.x && this->y == vec.y);
}
