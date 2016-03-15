/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 15 15:43:06 2016 Adrien WERY
*/

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include "Vector2.hpp"

class AComponent {
private:
    Vector2	pos;
public:
    AComponent(Vector2 const &pos);
    AComponent(int x, int y);
    virtual ~AComponent ();
    Vector2 const   &getPos() const;
    void            setPos(const Vector2 &pos);
};

#endif /* !ACOMPONENT_HPP_ */
