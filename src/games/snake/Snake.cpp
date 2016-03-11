/*
** Snake.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:40:10 2016 Nicolas Constanty
** Last update	Fri Mar 11 18:22:50 2016 Adrien WERY
*/

#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2(1000, 1000))
{}

Snake::~Snake ()
{}

std::stack<AComponent*>     Snake::compute(int key)
{
    std::stack<AComponent*> components;
  (void)key;
  return (components);
}

std::stack<AComponent*>     Snake::getInfos()
{
    std::stack<AComponent*> components;
    return (components);
}

void                        Snake::restart()
{

}
