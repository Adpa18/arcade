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
