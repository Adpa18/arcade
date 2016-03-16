/*
** GameComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:36:54 2016 Nicolas Constanty
** Last update	Wed Mar 16 07:22:41 2016 Nicolas Constanty
*/

#ifndef GAMECOMPONENT_HPP_
# define GAMECOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class GameComponent : public AComponent {
private:
    char        spriteText;
    std::string fileSprite2D;
    void        *sprite3D;
public:
  GameComponent(Vector2 const &pos, Vector2 const &size, ComponentColor color, void *sprite3D, char const &spriteText,
     std::string const &sprite2D);
  virtual ~GameComponent();

  char const &getSpriteText() const;
  std::string const &getSprite2D() const;
  void              *getSprite3D() const;
};

#endif /* !GAMECOMPONENT_HPP_ */
