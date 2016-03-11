/*
** Sdl2.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Fri Mar 11 14:49:21 2016 Nicolas Constanty
** Last update	Fri Mar 11 18:25:34 2016 Adrien WERY
*/

#include <iostream>
#include "Sdl2.hpp"

Sdl2::Sdl2 (void)
{
    std::cout << "StartInit => Lib Sdl2" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
        throw std::runtime_error(std::string("Can't init SDL") + SDL_GetError());
}

Sdl2::~Sdl2 ()
{
    SDL_DestroyWindow(this->win);
     SDL_Quit();
}

void  Sdl2::init(const std::string &name, Vector2 size, std::stack<AComponent*> cache)
{
    this->win = SDL_CreateWindow("SDL2",SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
}

int Sdl2::eventManagment()
{
  int key = 1;
  return (key);
}

void Sdl2::display(std::stack<AComponent*>)
{
  // Object2D *obj = static_cast<Object2D *>(objects.top());
  // Vector2 vec = obj->getCoord<Vector2>();
  // std::cout << "x = " << vec.x << " y = " << vec.y << std::endl;
}
