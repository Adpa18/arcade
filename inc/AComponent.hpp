/*
** AComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Wed Mar 09 15:36:17 2016 Nicolas Constanty
*/

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include "Vector2.hpp"

class AComponent {
private:
  Vector2	pos;
public:
  AComponent(Vector2 pos);
  AComponent(int x, int y);
  virtual ~AComponent ();
  Vector2 const &getPos() const;
};

#endif /* !ACOMPONENT_HPP_ */
