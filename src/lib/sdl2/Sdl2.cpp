/*
** Sdl2.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:47:26 2016 Adrien WERY
** Last update	Wed Mar 16 22:04:37 2016 Adrien WERY
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
    for (std::map<std::string, SDL_Texture*>::iterator it = this->tex.begin(); it != this->tex.end(); ++it) {
        SDL_DestroyTexture(it->second);
    }
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
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 0);
    SDL_RenderClear(this->render);
    this->display(cache);
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
    SDL_Rect        rect;
    AComponent      *obj;
    GameComponent   *Gobj;
    TextComponent   *Tobj;
    unsigned int    colorInt;

    while (!components.empty()) {
        obj = components.top();
        components.pop();
        rect.x = obj->getPos().x;
        rect.y = obj->getPos().y;
        rect.w = obj->getSize().x;
        rect.h = obj->getSize().y;
        if ((Gobj = dynamic_cast<GameComponent*>(obj)) && !Gobj->getSprite2D().empty()) {
            if (this->tex[Gobj->getSprite2D()] == 0) {
                this->tex[Gobj->getSprite2D()] = IMG_LoadTexture(this->render, std::string("./assets/sprites2D/" + Gobj->getSprite2D()).c_str());
            }
            SDL_SetRenderDrawColor(this->render, 0, 0, 0, 0);
            SDL_RenderFillRect(this->render, &rect);
            SDL_RenderCopy(this->render, this->tex[Gobj->getSprite2D()], NULL, &rect);
        } else if ((Tobj = dynamic_cast<TextComponent*>(obj))) {
            this->affText(*Tobj);
        } else {
            colorInt = this->colors[obj->getColor()];
            SDL_SetRenderDrawColor(this->render, ((colorInt >> 16) & 255), ((colorInt >> 8) & 255), ((colorInt) & 255), ((colorInt >> 24) & 255));
            SDL_RenderFillRect(this->render, &rect);
        }
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
    SDL_Rect        rect;
    int             w = 1;
    int             h = 1;

    colorInt = this->colors[text.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    fontName = text.getFontName();
    if (this->fonts[fontName] == 0) {
        this->fonts[fontName] = TTF_OpenFont(std::string("./assets/fonts/" + fontName + ".ttf").c_str(), text.getFontSize());
    }
    surface = TTF_RenderText_Blended(fonts[fontName], text.getText().c_str(), color);
    texture = SDL_CreateTextureFromSurface(this->render, surface);
    SDL_FreeSurface(surface);
    rect.x = text.getPos().x;
    rect.y = text.getPos().y;
    w = h = 1;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(this->render, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
