/*
** UIComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Mon Mar 28 21:23:34 2016 Nicolas Constanty
*/

#include "UIComponent.hpp"

UIComponent::UIComponent(Vector2<int> const &p, Vector2<int> const &s, ComponentColor color, const std::string &text,
    const std::string &fontName, unsigned int fontSize)
    : AComponent(p, s, color)
{
    this->text = text;
    this->fontName = fontName;
    this->fontSize = fontSize;
}

UIComponent::~UIComponent ()
{

}

const std::string   &UIComponent::getText() const
{
    return (this->text);
}

const std::string   &UIComponent::getFontName() const
{
    return (this->fontName);
}

unsigned int        UIComponent::getFontSize() const
{
    return (this->fontSize);
}

void                UIComponent::setText(const std::string &text)
{
    this->text = text;
}

void                UIComponent::setFontName(const std::string &fontName)
{
    this->fontName = fontName;
}

void                UIComponent::setFontSize(unsigned int fontSize)
{
    this->fontSize = fontSize;
}
