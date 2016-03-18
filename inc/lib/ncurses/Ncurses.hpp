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
# include "UIComponent.hpp"


class Ncurses : public IGraph {
private:
    Vector2         size;
  bool				valid_size;
  ncurses::Window	*wind;
  ncurses::Window	*main_wind;
  std::map<int, int>    keyMap = {
      {27, ESC},
      {KEY_UP, UP}, {KEY_DOWN, DOWN}, {KEY_LEFT, LEFT}, {KEY_RIGHT, RIGHT},
      {48, KEY_0}, {49, KEY_1}, {50, KEY_2}, {51, KEY_3},
      {52, KEY_4}, {53, KEY_5}, {54, KEY_6}, {55, KEY_7},
      {56, KEY_8}, {57, KEY_9}
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
  virtual void    destroy();
};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}


#endif /* !NCURSES_HPP_ */
