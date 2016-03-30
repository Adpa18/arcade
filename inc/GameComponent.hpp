/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 03:25:20Nicolas Constanty
** Last update	Wed Mar 30 13:26:29 2016 Nicolas Constanty
*/

#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class GameComponent : public AComponent {
public:
  enum Shapes
  {
    CUBE_LARGE,
    CUBE_MEDIUM,
    CUBE_SMALL,
    SPHERE_LARGE,
    SPHERE_MEDIUM,
    SPHERE_SMALL
  };
private:
  Shapes          sprite3D;
  std::string     spriteText;
  std::string     fileSprite2D;
  Vector2<double> dim;

public:
  GameComponent(Vector2<double> const &pos, AComponent::ComponentColor color,
    Shapes sprite3D, std::string const &spriteText,
    std::string const &sprite2D);
  virtual ~GameComponent();
  GameComponent(Vector2<double> const &pos, Vector2<double> const &size, ComponentColor color,
      char const &spriteText, std::string const &sprite2D, Shapes sprite3D);

  std::string const &getSpriteText() const;
  std::string const &getSprite2D() const;
  Shapes            getSprite3D() const;
  void              setSpriteText(const char &spriteText);
  void              setSprite2D(const std::string &sprite2D);
  void              setSprite3D(Shapes sprite3D);
  Vector2<double> const &getDim() const;

};

#endif /* !GAMECOMPONENT_HPP_ */
