/*
** UIComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Wed Mar 30 17:28:12 2016 Nicolas Constanty
*/

#ifndef UIADVANCECOMPONENT_HPP_
# define UIADVANCECOMPONENT_HPP_

# include "UIComponent.hpp"

# define FONT_PATH "./assets/fonts"

class UIAdvanceComponent : public UIComponent {

private:
  std::string     fontName;
  unsigned int    fontSize;
 public:
   UIAdvanceComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color, const std::string &text,
            const std::string &fontName, unsigned int fontSize);
    virtual             ~UIAdvanceComponent();
    const std::string   &getText() const;
    const std::string   &getFontName() const;
    unsigned int        getFontSize() const;
    void                setFontName(const std::string &fontName);
    void                setFontSize(unsigned int fontSize);
};

#endif /* !UIADVANCECOMPONENT_HPP_ */
