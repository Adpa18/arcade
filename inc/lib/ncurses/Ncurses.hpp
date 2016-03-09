/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Wed Mar 09 07:05:57 2016 Nicolas Constanty
*/

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <cstdlib>
# include <unistd.h>
# include <ncurses.h>
# include "IGraph.hpp"
# include "Object2D.hpp"

class Ncurses : public IGraph {
private:
  std::stack<Object2D *> toto;
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual void eventManagment();
  virtual void display(std::stack<Object *>);
  virtual size_t getKey() const;
};

IGraph *loadLib()
{
  return (new Ncurses());
}

# include "Window.hpp"

#endif /* !NCURSES_HPP_ */
