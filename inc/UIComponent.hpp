/*
** UIComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Thu Mar 17 13:32:54 2016 Adrien WERY
*/

#ifndef UICOMPONENT_HPP_
# define UICOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

# define FONT_PATH "./assets/fonts"

class UIComponent : public AComponent {
private:
    std::string     text;
    std::string     fontName;
    unsigned int    fontSize;
public:
    UIComponent(Vector2 const &p, Vector2 const &s, ComponentColor color, const std::string &text,
            const std::string &fontName, unsigned int fontSize);
    virtual ~UIComponent();
    const std::string   &getText() const;
    const std::string   &getFontName() const;
    unsigned int        getFontSize() const;
    void                setText(const std::string &text);
    void                setFontName(const std::string &fontName);
    void                setFontSize(unsigned int fontSize);
};

#endif /* !UICOMPONENT_HPP_ */
