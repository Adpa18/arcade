/*
** Object3D.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:58:05 2016 Nicolas Constanty
** Last update	Wed Mar 09 00:05:34 2016 Nicolas Constanty
*/

#ifndef OBJECT3D_HPP_
# define OBJECT3D_HPP_

# include "Object.hpp"

enum ShapeEnum {SPHERE, CUBE, PLAN, CONE, CYLINDER, DISK};

class Object3D : public Object {
private:
  void *fptr;
  ShapeEnum type;
public:
  Object3D(void *newFptr, ShapeEnum newType, Vector2 const &coord,
     Vector2 const &dim);
  virtual		~Object3D();
  void      *getFptr() const;
  ShapeEnum	getType() const;
};

#endif /* !OBJECT3D_HPP_ */
