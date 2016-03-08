/*
** vector2.hpp for
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:07:00 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:14:40 2016 Nicolas Constanty
*/

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <cstdlib>

class Vector2 {
public:
  size_t x;
  size_t y;
  Vector2 (size_t x, size_t y);
  virtual ~Vector2 ();
  Vector2(const Vector2 &obj);
  Vector2  &operator=(const Vector2 &obj);
};

#endif /* !VECTOR2_HPP_ */
