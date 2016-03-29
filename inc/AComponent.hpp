/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:22:39 2016 Nicolas Constanty
*/

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include "Vector2.hpp"

class AComponent {
public:
  enum ComponentColor
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  };
private:
  Vector2<double>	        pos;
  ComponentColor          color;
  // Vector2<double>	        size;
public:
    AComponent(int x, int y, enum ComponentColor color);
    AComponent(Vector2<double> const &pos, enum ComponentColor color);
    virtual ~AComponent ();
    // AComponent(Vector2<double> const &pos, Vector2<double> const &size, ComponentColor color);
public:
    Vector2<double> const	&getPos() const;
    enum ComponentColor		getColor() const;
    // Vector2<double> const   &getSize() const;
public:
    void	setColor(ComponentColor color);
    void	setPos(const Vector2<double> &pos);
    // void            setSize(const Vector2<double> &pos);
};

#endif /* !ACOMPONENT_HPP_ */
