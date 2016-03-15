/*
** UIComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:40:56 2016 Nicolas Constanty
** Last update	Tue Mar 15 19:32:41 2016 Adrien WERY
*/

#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"

class UIComponent : public AComponent {
private:
  Vector2       dim;
  std::string   text;
public:
  UIComponent(Vector2 const &pos, ComponentColor color, Vector2 const &dim, std::string const &);
  virtual ~UIComponent();

  Vector2 const     &getDim() const;
  std::string const &getString() const;
};

#endif /* !UICOMPONENT_HPP_ */
