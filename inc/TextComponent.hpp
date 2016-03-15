/*
** TextComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Tue Mar 15 11:52:28 2016 Adrien WERY
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
    unsigned int    rgba;
public:
    TextComponent(Vector2 const &p, const std::string &text,
            const std::string &fontName, unsigned int fontSize, unsigned int rgba);
    virtual ~TextComponent();
    const std::string   &getText() const;
    const std::string   &getFontName() const;
    unsigned int        getFontSize() const;
    unsigned int        getColor() const;
};

#endif /* !TEXTCOMPONENT_HPP_ */
