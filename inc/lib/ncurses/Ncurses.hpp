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
# include "HighScoreComponent.hpp"

class Ncurses : public IGraph {
private:
    int             i;
  Vector2<double>   size;
  bool              valid_size;
  ncurses::Window	*wind;
  std::map<AComponent*, WINDOW*> texts;
  std::stack<Vector2<double>>   old_component;
  std::stack<WINDOW *>	        old_componentUI;

  std::map<int, int>    keyMap = {
      {27, ArcadeSystem::Exit},
      {KEY_UP, ArcadeSystem::ArrowUp}, {KEY_DOWN, ArcadeSystem::ArrowDown}, {KEY_LEFT, ArcadeSystem::ArrowLeft}, {KEY_RIGHT, ArcadeSystem::ArrowRight},
      {50, ArcadeSystem::PrevGraph}, {51, ArcadeSystem::NextGraph},
      {52, ArcadeSystem::NextGame}, {53, ArcadeSystem::NextGame},
      {56, ArcadeSystem::Restart}, {57, ArcadeSystem::Home},
      {'p', ArcadeSystem::Pause}, {10, ArcadeSystem::Enter}
  };


  bool 	        invalidSize(Vector2<double> const &size, Vector2<double> const &pos);
  void			initMainWindow();
  int			resizeTerm();
public:
  Ncurses (void);
  virtual ~Ncurses ();

  virtual int eventManagment();
  virtual void  display(std::stack<AComponent*>);
  void          displayGame(const GameComponent &game);
  void          displayUI(const UIComponent &ui);
  void          displayHighScore(UIComponent const * const *uiComponents);
  // virtual void  init(const std::string &name);
  // virtual void  init(const std::string &name, std::stack<AComponent*> cache);
  virtual void  setTitle(const std::string &title){(void)title;}
};

extern "C" IGraph *loadLib()
{
  return (new Ncurses());
}


#endif /* !NCURSES_HPP_ */
