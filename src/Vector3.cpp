/*
** Vector3.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:10:08 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:11:33 2016 Nicolas Constanty
*/

#include "Vector3.hpp"

Vector3::Vector3(size_t newX, size_t newY, size_t newZ)
{
  this->x = newX;
  this->y = newY;
  this->z = newZ;
}

Vector3::~Vector3()
{}

Vector3::Vector3(const Vector3 &obj)
{
  *this = obj;
}

Vector3 &Vector3::operator=(const Vector3 &vec)
{
  this->x = vec.x;
  this->y = vec.y;
  this->z = vec.z;
  return *this;
}
