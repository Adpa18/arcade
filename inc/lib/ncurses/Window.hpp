#ifndef WINDOW_HPP_
# define WINDOW_HPP_

# include <ncurses.h>
# include "Vector2.hpp"

namespace ncurses {
  class Window {
  private:
    Vector2<double>	size;
    Vector2<double>	pos;
    WINDOW	*parent;
    WINDOW	*wind;
  public:
    Window (Vector2<double> &s, Vector2<double> &p, WINDOW *pa);
    virtual ~Window ();
    Vector2<double>	getSize() const;
    void		setSize();
    Vector2<double> getPos() const;
    void		setPos();
    WINDOW	*getWind() const;
    void	  close();
    void		setWind(Vector2<double> &s, Vector2<double> &p, WINDOW *pa);
  };
};


#endif /* !WINDOW_HPP_ */
