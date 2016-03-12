/*
** TextComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:29:50 2016 Nicolas Constanty
** Last update	Fri Mar 11 21:15:11 2016 Adrien WERY
*/

#ifndef TEXTCOMPONENT_HPP_
# define TEXTCOMPONENT_HPP_

# include <string>
# include "Vector2.hpp"

# define FONT_PATH "./assets/fonts"

class TextComponent {
private:
    std::string     text;
    std::string     fontName;
    unsigned int    fontSize;
    unsigned int    rgba;
public:
    TextComponent();
    virtual ~TextComponent();
    const std::string   &getText() const;
    const std::string   &getFontName() const;
    unsigned int        getFontSize() const;
    unsigned int        getColor() const;
};

#endif /* !TEXTCOMPONENT_HPP_ */
