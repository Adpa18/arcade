/*
** TextComponent.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Mar 11 20:58:21 2016 Adrien WERY
** Last update	Fri Mar 11 21:44:42 2016 Adrien WERY
*/

#include "TextComponent.hpp"

TextComponent::TextComponent()
{

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
