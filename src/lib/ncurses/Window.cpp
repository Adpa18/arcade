/*
** window.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:32:04 2016 Nicolas Constanty
** Last update	Tue Mar 08 19:07:04 2016 Nicolas Constanty
*/
#include "Window.hpp"

Window::Window (Vector2 &s, Vector2 &p, WINDOW *pa)
 : size(s), pos(p)
{
  this->parent = pa;
  if (!this->parent)
    this->wind = newwin(this->size.x, this->size.y, this->pos.x, this->pos.y);
  box(this->wind, 0 , 0);
  wrefresh(this->wind);
}

Window::~Window ()
{}

Vector2	Window::getSize() const
{
  return (this->size);
}

void		Window::setSize()
{}

Vector2 Window::getPos() const
{
  return (this->size);
}

void		Window::setPos()
{}
