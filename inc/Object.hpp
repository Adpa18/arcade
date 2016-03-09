/*
** AObject.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:12:30 2016 Nicolas Constanty
** Last update	Wed Mar 09 00:02:29 2016 Nicolas Constanty
*/

#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include "Vector2.hpp"

class Object {
protected:
  Vector2 coord;
  Vector2 dim;
public:
  Object(Vector2 const &newCoord, Vector2 const &newDim);
  virtual ~Object();
  template<typename T>
  T const &getCoord() const;
  template<typename T>
  T const &getDim() const;
};

#endif /* !OBJECT_HPP_ */
