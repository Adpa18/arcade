/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Wed Mar 09 19:36:14 2016 Nicolas Constanty
*/

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <cstdlib>
# include <unistd.h>
# include <ncurses.h>
# include "IGraph.hpp"

class Ncurses : public IGraph {
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual void eventManagment();
  virtual void display(std::stack<AComponent> *);
  virtual size_t getKey() const;
};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}

# include "Window.hpp"

#endif /* !NCURSES_HPP_ */
