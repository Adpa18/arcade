#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include <cstdlib>
# include <unistd.h>
# include <map>
# include <ncurses.h>
# include "IGraph.hpp"
# include "Window.hpp"
# include "GameComponent.hpp"
# include "AudioComponent.hpp"
# include "UIComponent.hpp"


class Ncurses : public IGraph {
private:
  Vector2<double> size;
  bool						is_init;
  bool						is_destroy;
  bool				    valid_size;
  ncurses::Window	*wind;
  std::map<int, int>    keyMap = {
      {27, ArcadeSystem::Exit},
      {KEY_UP, ArcadeSystem::ArrowUp}, {KEY_DOWN, ArcadeSystem::ArrowDown}, {KEY_LEFT, ArcadeSystem::ArrowLeft}, {KEY_RIGHT, ArcadeSystem::ArrowRight},
      {50, ArcadeSystem::PrevGraph}, {51, ArcadeSystem::NextGraph},
      {52, ArcadeSystem::NextGame}, {53, ArcadeSystem::NextGame},
      {56, ArcadeSystem::Restart}, {57, ArcadeSystem::Home}
  };
  std::map<AComponent *, WINDOW *> texts;

  bool 						invalidSize(Vector2<double> const &size, Vector2<double> const &pos);
  void						initMainWindow();
  int							resizeTerm();
  void            initc(Vector2<double> s);
  std::stack<Vector2<double>>	old_component;
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual int eventManagment();
  virtual void display(std::stack<AComponent*>);
  virtual void init(const std::string &name, Vector2<double> s, std::stack<AComponent*> cache);
  virtual void    destroy();
};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}

extern "C" void initLib(IGraph *graph, const std::string &name, Vector2<double> size, std::stack<AComponent *> cache)
{
  static_cast<Ncurses *>(graph)->init(name, size, cache);
}

extern "C" void destroyLib(IGraph *graph)
{
  static_cast<Ncurses *>(graph)->destroy();
}


#endif /* !NCURSES_HPP_ */
