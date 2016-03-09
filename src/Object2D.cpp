/*
** Object2D.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:54:27 2016 Nicolas Constanty
** Last update	Tue Mar 08 23:49:31 2016 Nicolas Constanty
*/

#include "Object2D.hpp"

Object2D::Object2D(std::string const &newFileName, Vector2 const &coord,
  Vector2 const &dim) : Object(coord, dim)
{
  this->fileName = newFileName;
}

Object2D::~Object2D()
{}

std::string const &Object2D::getFIleName() const
{
  return (this->fileName);
}
