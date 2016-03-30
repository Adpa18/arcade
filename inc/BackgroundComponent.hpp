#ifndef BACKGROUNDCOMPONENT_HPP_
# define BACKGROUNDCOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

class BackgroundComponent : public AComponent {
private:
    std::string     sprite2D;
    Vector2<double> dim;
public:
  BackgroundComponent(Vector2<double> pos, Vector2<double> size, ComponentColor color, std::string const &sprite2D);
  virtual ~BackgroundComponent();

  std::string const &getSprite2D() const;
  void              setSprite2D(const std::string &sprite2D);
  Vector2<double> const &getDim() const;
};

#endif /* !BACKGROUNDCOMPONENT_HPP_ */
