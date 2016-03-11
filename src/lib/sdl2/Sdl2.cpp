/*
** Sdl2.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Fri Mar 11 14:49:21 2016 Nicolas Constanty
** Last update	Fri Mar 11 14:52:58 2016 Nicolas Constanty
*/

#include <iostream>
#include "Sdl2.hpp"

Sdl2::Sdl2 (void)
{
  std::cout << "StartInit => Lib Sdl2" << std::endl;
}

Sdl2::~Sdl2 ()
{
}

void	Sdl2::initMainWindow()
{

}

bool	Sdl2::invalidSize(int width, int height, Vector2 const &size, Vector2 const &pos)
{

  return (false);
}

int	Sdl2::resizeTerm()
{
  return (1);
}

int Sdl2::eventManagment()
{
  int key = 1;
  return (key);
}

void Sdl2::display(std::stack<AComponent> *)
{
  // Object2D *obj = static_cast<Object2D *>(objects.top());
  // Vector2 vec = obj->getCoord<Vector2>();
  // std::cout << "x = " << vec.x << " y = " << vec.y << std::endl;
}
