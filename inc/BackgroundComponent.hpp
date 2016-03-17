/*
** BackgroundComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:32:30 2016 Nicolas Constanty
** Last update	Thu Mar 17 13:24:13 2016 Adrien WERY
*/

#ifndef BACKGROUNDCOMPONENT_HPP_
# define BACKGROUNDCOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class BackgroundComponent : public AComponent {
private:
    std::string     sprite2D;
public:
  BackgroundComponent(Vector2 pos, Vector2 size, ComponentColor color, std::string const &sprite2D);
  virtual ~BackgroundComponent();

  std::string const &getSprite2D() const;
  void              setSprite2D(const std::string &sprite2D);
};

#endif /* !BACKGROUNDCOMPONENT_HPP_ */
