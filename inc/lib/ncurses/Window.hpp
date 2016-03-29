/*
** window.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:32:04 2016 Nicolas Constanty
** Last update	Tue Mar 29 16:35:56 2016 Adrien WERY
*/

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

# include "ncurses.h"
# include "Vector2.hpp"

namespace ncurses {
  class Window {
  private:
    Vector2<int>	size;
    Vector2<int>	pos;
    WINDOW	*parent;
    WINDOW	*wind;
  public:
    Window (Vector2<int> &s, Vector2<int> &p, WINDOW *pa);
    virtual ~Window ();
    Vector2<int>	getSize() const;
    void		setSize();
    Vector2<int> getPos() const;
    void		setPos();
    WINDOW	*getWind() const;
    void	  close();
    void		setWind(Vector2<int> &s, Vector2<int> &p, WINDOW *pa);
  };
};


#endif /* !WINDOW_HPP_ */
