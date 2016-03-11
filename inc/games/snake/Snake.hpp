/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:32:51 2016 Nicolas Constanty
** Last update	Fri Mar 11 18:28:31 2016 Adrien WERY
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include "AGame.hpp"
# include "Utils.hpp"

class Snake : public AGame {
public:
  Snake ();
  virtual ~Snake ();
  virtual std::stack<AComponent*>   compute(int key);
  virtual std::stack<AComponent*>   getInfos();
  virtual void                      restart();
};

extern "C" AGame *loadGame()
{
  return (new Snake());
}

#endif /* !SNAKE_HPP_ */
