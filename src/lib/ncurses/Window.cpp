/*
** window.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:32:04 2016 Nicolas Constanty
** Last update	Wed Mar 30 15:40:37 2016 Nicolas Constanty
*/
#include <iostream>
#include "Window.hpp"

ncurses::Window::Window (Vector2<double> &s, Vector2<double> &p, WINDOW *pa)
 : size(s), pos(p)
{
  this->setWind(s, p, pa);
}

ncurses::Window::~Window ()
{
  if (this->wind)
    delwin(this->wind);
}

Vector2<double>	ncurses::Window::getSize() const
{
  return (this->size);
}

void		ncurses::Window::setSize()
{}

Vector2<double> ncurses::Window::getPos() const
{
  return (this->size);
}

void		ncurses::Window::setPos()
{}

void		ncurses::Window::setWind(Vector2<double> &s, Vector2<double> &p, WINDOW *pa)
{

  this->size = s;
  this->pos = p;
  this->parent = pa;
  if (!this->parent)
    this->wind = newwin(this->size.y, this->size.x, this->pos.y, this->pos.x);
  else
    this->wind = subwin(pa, this->size.y, this->size.x, this->pos.y, this->pos.x);
  wrefresh(this->wind);
}

WINDOW *ncurses::Window::getWind() const
{
  return (this->wind);
}
void ncurses::Window::close()
{
  if (this->parent)
  {
    delwin(this->parent);
    this->parent = NULL;
    this->wind = NULL;
  }
  else if (this->wind)
  {
    delwin(this->wind);
    this->parent = NULL;
    this->wind = NULL;
  }
}
