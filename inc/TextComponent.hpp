/*
** TextComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Wed Mar 16 13:52:43 2016 Adrien WERY
*/

#ifndef TEXTCOMPONENT_HPP_
# define TEXTCOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"
# include "Vector2.hpp"

# define FONT_PATH "./assets/fonts"

class TextComponent : public AComponent {
private:
    std::string     text;
    std::string     fontName;
    unsigned int    fontSize;
public:
    TextComponent(Vector2 const &p, ComponentColor color, const std::string &text,
            const std::string &fontName, unsigned int fontSize);
    virtual ~TextComponent();
    const std::string   &getText() const;
    const std::string   &getFontName() const;
    unsigned int        getFontSize() const;
    void                setText(const std::string &text);
    void                setFontName(const std::string &fontName);
    void                setFontSize(unsigned int fontSize);
};

#endif /* !TEXTCOMPONENT_HPP_ */
