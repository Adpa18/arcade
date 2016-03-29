/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:32:30 2016 Nicolas Constanty
** Last update	Mon Mar 28 21:21:11 2016 Nicolas Constanty
*/

#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class GameComponent : public AComponent {
private:
    char        spriteText;
    std::string sprite2D;
    void        *sprite3D;
public:
  GameComponent(Vector2<int> const &pos, Vector2<int> const &size, ComponentColor color,
      char const &spriteText, std::string const &sprite2D, void *sprite3D);
  virtual ~GameComponent();

  char const        &getSpriteText() const;
  std::string const &getSprite2D() const;
  void              *getSprite3D() const;
  void              setSpriteText(const char &spriteText);
  void              setSprite2D(const std::string &sprite2D);
  void              setSprite3D(void *sprite3D);
};

#endif /* !GAMECOMPONENT_HPP_ */
