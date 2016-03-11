/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Fri Mar 11 14:46:22 2016 Nicolas Constanty
*/

#ifndef SDL2_HPP_
# define SDL2_HPP_

# include <SDL2/SDL.h>
# include "IGraph.hpp"


class Sdl2 : public IGraph {
private:
  bool						valid_size;

  bool 						invalidSize(int w, int h, Vector2 const &size, Vector2 const &pos);
  void						initMainWindow();
  int							resizeTerm();
public:
  Sdl2 (void);
  virtual ~Sdl2 ();

  virtual int eventManagment();
  virtual void display(std::stack<AComponent> *);

};

extern "C" IGraph *loadLib()
{
  return (new Sdl2());
}


#endif /* !SDL2_HPP_ */
