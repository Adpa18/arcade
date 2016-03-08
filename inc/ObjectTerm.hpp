/*
** ObjectTerm.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:26:18 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:06:47 2016 Nicolas Constanty
*/

#ifndef OBJECTTERM_HPP_
# define OBJECTTERM_HPP_

# include "Object.hpp"

class ObjectTerm : public Object {
private:
  char carac;
public:
  ObjectTerm(char c, Vector2 const &coord, Vector2 const &dim);
  virtual ~ObjectTerm ();
  char getCaract() const;
};

#endif /* !OBJECTTERM_HPP_ */
