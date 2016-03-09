/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:32:51 2016 Nicolas Constanty
** Last update	Wed Mar 09 03:47:13 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include "Interfaces.hpp"
# include "Utils.hpp"

class Snake : public IGame {
private:
  void	*lptr;
  IGraph *graph;
public:
  Snake (void *);
  virtual ~Snake ();
  virtual void compute();
};

IGame *loadGame(void *ptr)
{
  return (new Snake(ptr));
}


#endif /* !SNAKE_HPP_ */
