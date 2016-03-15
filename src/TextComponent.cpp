/*
** TextComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Tue Mar 15 12:04:20 2016 Adrien WERY
*/

#include "TextComponent.hpp"

TextComponent::TextComponent(Vector2 const &p, const std::string &text,
    const std::string &fontName, unsigned int fontSize, unsigned int rgba)
    : AComponent(p)
{
    this->text = text;
    this->fontName = fontName;
    this->fontSize = fontSize;
    this->rgba = rgba;
}

TextComponent::~TextComponent ()
{

}

const std::string   &TextComponent::getText() const
{
    return (this->text);
}

const std::string   &TextComponent::getFontName() const
{
    return (this->fontName);
}

unsigned int        TextComponent::getFontSize() const
{
    return (this->fontSize);
}

unsigned int        TextComponent::getColor() const
{
    return (this->rgba);
}
