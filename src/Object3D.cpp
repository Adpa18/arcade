/*
** Object3D.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:02:12 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:05:44 2016 Nicolas Constanty
*/

#include "Object3D.hpp"

Object3D::Object3D(void *newFptr, ShapeEnum newType, Vector2 const &coord,
 Vector2 const &dim) : Object(coord, dim)
{
  this->fptr = newFptr;
  this->type = newType;
}
Object3D::~Object3D()
{}

void      *Object3D::getFptr() const
{
  return (this->fptr);
}

ShapeEnum	Object3D::getType() const
{
  return (this->type);
}
