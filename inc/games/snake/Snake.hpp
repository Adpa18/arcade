/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:32:51 2016 Nicolas Constanty
** Last update	Wed Mar 09 19:35:55 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include "Interfaces.hpp"
# include "Utils.hpp"

class Snake : public IGame {
public:
  Snake ();
  virtual ~Snake ();
  virtual std::stack<AComponent> *compute(size_t key);
};

extern "C" IGame *loadGame()
{
  return (new Snake());
}

#endif /* !SNAKE_HPP_ */
