/*
** window.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:32:04 2016 Nicolas Constanty
** Last update	Tue Mar 08 22:15:49 2016 Nicolas Constanty
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

# include "Vector2.hpp"

class Window {
private:
  Vector2	size;
  Vector2	pos;
  WINDOW	*parent;
  WINDOW	*wind;
public:
  Window (Vector2 &s, Vector2 &p, WINDOW *pa);
  virtual ~Window ();
  Vector2	getSize() const;
  void		setSize();
  Vector2 getPos() const;
  void		setPos();
};

#endif /* !WINDOW_HPP_ */
