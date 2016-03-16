/*
** Sdl2.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Fri Mar 11 14:49:21 2016 Nicolas Constanty
** Last update	Wed Mar 16 08:24:52 2016 Nicolas Constanty
*/

#include <iostream>
#include "Sdl2.hpp"

Sdl2::Sdl2 (void)
{
    std::cout << "StartInit => Lib Sdl2" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(std::string("Can't init SDL") + SDL_GetError());
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
        throw std::runtime_error(std::string("Can't init IMG") + SDL_GetError());
    if (TTF_Init() == -1)
        throw std::runtime_error(std::string("Can't init TTF") + SDL_GetError());
}

Sdl2::~Sdl2 ()
{
    SDL_DestroyWindow(this->win);
    SDL_DestroyRenderer(this->render);
    // for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) {
    //     TTF_CloseFont(it->second);
    // }
    TTF_Quit();
    SDL_Quit();
}

void  Sdl2::init(const std::string &name, Vector2 size, std::stack<AComponent*> cache)
{
    if (!(this->win = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_SHOWN)))
        throw std::runtime_error(std::string("Can't create Window") + SDL_GetError());
    if (!(this->render = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED)))
        throw std::runtime_error(std::string("Can't render Window") + SDL_GetError());
    this->affText(TextComponent(Vector2(10, 10), GREEN, "Snake", "frenchy", 24));
    SDL_SetRenderDrawColor(this->render, 255, 255, 0, 255);
    this->display(cache);
    while (!this->old_pos.empty()) {
        this->old_pos.pop();
    }
}

int Sdl2::eventManagment()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.key.type != SDL_KEYDOWN)
        return (-1);
    return (this->keyMap[event.key.keysym.sym]);
}

void Sdl2::display(std::stack<AComponent*> components)
{
    SDL_Rect    rect;
    AComponent  *obj;
    unsigned int    colorInt;

    while (!components.empty()) {
        obj = components.top();
        components.pop();
        rect.x = obj->getPos().x;
        rect.y = obj->getPos().y;
        rect.w = obj->getSize().x;
        rect.h = obj->getSize().y;
        this->old_pos.push(rect);
        colorInt = this->colors[obj->getColor()];
        SDL_SetRenderDrawColor(this->render, ((colorInt >> 8) & 255), ((colorInt >> 16) & 255), ((colorInt >> 24) & 255), ((colorInt) & 255));
        SDL_RenderFillRect(this->render, &rect);
    }
    SDL_RenderPresent(this->render);
}

void    Sdl2::affText(const TextComponent &text)
{
    std::string     fontName;
    unsigned int    colorInt;
    SDL_Color       color;
    SDL_Surface*    surface;
    SDL_Texture     *texture;
    SDL_Rect        rec;
    int             w = 1;
    int             h = 1;

    colorInt = this->colors[text.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    fontName = text.getFontName();
    // if (this->fonts[fontName] == 0) {
    //     this->fonts.insert(std::pair<std::string, TTF_Font*>(fontName,
    //         TTF_OpenFont(std::string("./assets/fonts/" + fontName + ".ttf").c_str(),
    //         text.getFontSize())));
    // }
    // surface = TTF_RenderText_Blended(fonts[fontName], text.getText().c_str(), color);
    surface = TTF_RenderText_Blended(TTF_OpenFont(
            std::string("./assets/fonts/" + fontName + ".ttf").c_str(),
            text.getFontSize()), text.getText().c_str(), color);
    texture = SDL_CreateTextureFromSurface(this->render, surface);
    SDL_FreeSurface(surface);
    rec.x = text.getPos().x;
    rec.y = text.getPos().y;
    w = h = 1;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rec.w = w;
    rec.h = h;
    SDL_RenderCopy(this->render, texture, NULL, &rec);
    SDL_DestroyTexture(texture);
    // SDL_BlitSurface(surface, NULL, ecran, &position)
}
