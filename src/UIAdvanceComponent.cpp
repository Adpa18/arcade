/*
** UIAdvanceComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Wed Mar 30 17:28:38 2016 Nicolas Constanty
*/

#include "UIAdvanceComponent.hpp"

UIAdvanceComponent::UIAdvanceComponent(Vector2<double> const &p, Vector2<double> const &s, ComponentColor color, const std::string &text,
    const std::string &fontName, unsigned int fontSize)
    : UIComponent(p, color, s, text)
{
    this->fontName = fontName;
    this->fontSize = fontSize;
}

UIAdvanceComponent::~UIAdvanceComponent ()
{

}

const std::string   &UIAdvanceComponent::getText() const
{
    return (this->text);
}

const std::string   &UIAdvanceComponent::getFontName() const
{
    return (this->fontName);
}

unsigned int        UIAdvanceComponent::getFontSize() const
{
    return (this->fontSize);
}

void                UIAdvanceComponent::setFontName(const std::string &fontName)
{
    this->fontName = fontName;
}

void                UIAdvanceComponent::setFontSize(unsigned int fontSize)
{
    this->fontSize = fontSize;
}
