/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Thu Mar 17 05:55:24 2016 Nicolas Constanty
*/

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <cstdlib>
# include <unistd.h>
# include <ncurses.h>
# include <map>
# include "IGraph.hpp"
# include "AGame.hpp"
# include "Window.hpp"
# include "GameComponent.hpp"
# include "AudioComponent.hpp"
# include "TextComponent.hpp"


class Ncurses : public IGraph {
private:
  bool				valid_size;
  ncurses::Window	*wind;
  ncurses::Window	*main_wind;
  std::map<int, int>    keyMap = {
      {27, ESC},
      {KEY_UP, UP}, {KEY_DOWN, DOWN}, {KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT}
  };
  std::map<AComponent *, WINDOW *> texts;

  bool 						invalidSize(int w, int h, Vector2 const &size, Vector2 const &pos);
  void						initMainWindow();
  int							resizeTerm();
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual int eventManagment();
  virtual void display(std::stack<AComponent*>);
  virtual void init(const std::string &name, Vector2 size, std::stack<AComponent*> cache);

};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}


#endif /* !NCURSES_HPP_ */
