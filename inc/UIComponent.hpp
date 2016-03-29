/*
** UIComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:29:28 2016 Nicolas Constanty
*/

#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

# define FONT_PATH "./assets/fonts"

class UIComponent : public AComponent {

protected:
  Vector2<double> dim;
  std::string text;

 public:
   UIComponent(Vector2<double> const &pos, enum ComponentColor color,
          Vector2<double> const &dim, std::string const &);
 virtual ~UIComponent();

 public:
  Vector2<double> const &getDim() const;
  std::string const     &getText() const;
// private:
//     std::string     text;
//     std::string     fontName;
//     unsigned int    fontSize;
//
// public:
//     UIComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color, const std::string &text,
//             const std::string &fontName, unsigned int fontSize);
//     virtual             ~UIComponent();
//     const std::string   &getText() const;
//     const std::string   &getFontName() const;
//     unsigned int        getFontSize() const;
//     void                setText(const std::string &text);
//     void                setFontName(const std::string &fontName);
//     void                setFontSize(unsigned int fontSize);
};

#endif /* !UICOMPONENT_HPP_ */
