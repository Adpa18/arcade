/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Thu Mar 10 15:44:33 2016 Nicolas Constanty
*/

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <cstdlib>
# include <unistd.h>
# include <ncurses.h>
# include "IGraph.hpp"
# include "Window.hpp"


class Ncurses : public IGraph {
private:
  bool						valid_size;
  ncurses::Window	*wind;
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual int eventManagment();
  virtual void display(std::stack<AComponent> *);

  bool invalidSize(int w, int h, Vector2 const &size, Vector2 const &pos);
};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}


#endif /* !NCURSES_HPP_ */
