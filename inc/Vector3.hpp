/*
** Vector3.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:09:49 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:18:49 2016 Nicolas Constanty
*/

#ifndef VECTOR3_HPP_
# define VECTOR3_HPP_

# include <cstdlib>

class Vector3 {
public:
  size_t x;
  size_t y;
  size_t z;
  Vector3(size_t newX, size_t newY, size_t newZ);
  Vector3(const Vector3 &obj);
  virtual 	~Vector3 ();
  Vector3		&operator=(const Vector3 &obj);
};

#endif /* !VECTOR3_HPP_ */
