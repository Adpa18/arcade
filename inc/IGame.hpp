/*
** IGame.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:38:09 2016 Nicolas Constanty
** Last update	Tue Mar 08 17:42:18 2016 Nicolas Constanty
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <stack>
#include "Object.hpp"

class IGame {
public:
  virtual std::stack<Object *> compute() = 0;
};

#endif /* !IGAME_HPP_ */
