/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:36:54 2016 Nicolas Constanty
** Last update	Wed Mar 16 11:41:02 2016 Adrien WERY
*/

#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class GameComponent : public AComponent {
private:
    std::string spriteText;
    std::string sprite2D;
    void        *sprite3D;
public:
  GameComponent(Vector2 const &pos, Vector2 const &size, ComponentColor color,
      std::string const &spriteText, std::string const &sprite2D, void *sprite3D);
  virtual ~GameComponent();

  std::string const &getSpriteText() const;
  std::string const &getSprite2D() const;
  void              *getSprite3D() const;
  void              setSpriteText(const std::string &spriteText);
  void              setSprite2D(const std::string &sprite2D);
  void              setSprite3D(void *sprite3D);
};

#endif /* !GAMECOMPONENT_HPP_ */
