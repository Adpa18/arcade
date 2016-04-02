#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

# define FONT_PATH "./assets/fonts"

class UIComponent : public AComponent {

protected:
  Vector2<double>   dim;
  std::string       text;

 public:
   UIComponent(Vector2<double> const &pos, enum ComponentColor color,
          Vector2<double> const &dim, std::string const &);
 virtual ~UIComponent();

 public:
  Vector2<double> const &getDim() const;
  std::string const     &getText() const;
  void                  setText(const std::string &text);
};

#endif /* !UICOMPONENT_HPP_ */
