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
  Vector2<double>   pos;
  ComponentColor    _color;
public:
    AComponent(int x, int y, enum ComponentColor color);
    AComponent(Vector2<double> const &pos, enum ComponentColor color);
    virtual ~AComponent ();
public:
    Vector2<double> const	&getPos() const;
    enum ComponentColor     getColor() const;
    void                    setColor(ComponentColor color);
    void	                setPos(const Vector2<double> &pos);
};

#endif /* !ACOMPONENT_HPP_ */
