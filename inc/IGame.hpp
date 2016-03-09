/*
** IGame.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:38:09 2016 Nicolas Constanty
** Last update	Wed Mar 09 19:42:03 2016 Nicolas Constanty
*/

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <stack>
# include <iostream>
# include "AComponent.hpp"

enum Libtype { _TERM , _2D, _3D};

class IGame {
public:
  virtual std::stack<AComponent> *compute(int key) = 0;
};

#endif /* !IGAME_HPP_ */
