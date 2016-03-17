/*
** TextComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Thu Mar 17 03:13:21 2016 Nicolas Constanty
*/

#include "TextComponent.hpp"

TextComponent::TextComponent(Vector2 const &p, Vector2 const &s, ComponentColor color, const std::string &text,
    const std::string &fontName, unsigned int fontSize)
    : AComponent(p, s, color)
{
    this->text = text;
    this->fontName = fontName;
    this->fontSize = fontSize;
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

void                TextComponent::setText(const std::string &text)
{
    this->text = text;
}

void                TextComponent::setFontName(const std::string &fontName)
{
    this->fontName = fontName;
}

void                TextComponent::setFontSize(unsigned int fontSize)
{
    this->fontSize = fontSize;
}
