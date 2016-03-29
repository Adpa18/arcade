/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Mon Mar 28 21:15:58 2016 Nicolas Constanty
*/

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include "Vector2.hpp"

enum ComponentColor {
    BLACK,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    MAGENTA,
    CYAN,
    WHITE
};

class AComponent {
private:
    Vector2<int>	        pos;
    Vector2<int>	        size;
    ComponentColor        color;
public:
    AComponent(Vector2<int> const &pos, ComponentColor color);
    AComponent(Vector2<int> const &pos, Vector2<int> const &size, ComponentColor color);
    AComponent(int x, int y, ComponentColor color);
    virtual ~AComponent ();
    Vector2<int> const   &getPos() const;
    void            setPos(const Vector2<int> &pos);
    Vector2<int> const   &getSize() const;
    void            setSize(const Vector2<int> &pos);
    ComponentColor const   &getColor() const;
    void            setColor(const ComponentColor color);
};

#endif /* !ACOMPONENT_HPP_ */
