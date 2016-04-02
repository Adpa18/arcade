#include <iostream>
#include "Sdl2.hpp"

Sdl2::Sdl2 (void) : size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string("Can't init SDL") + SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1) {
        throw std::runtime_error(std::string("Can't init IMG") + SDL_GetError());
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error(std::string("Can't init TTF") + SDL_GetError());
    }
    if (!(this->win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x * STEP, size.y * STEP, SDL_WINDOW_OPENGL))) {
        throw std::runtime_error(std::string("Can't create Window") + SDL_GetError());
    }
    if (!(this->render = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED))) {
        throw std::runtime_error(std::string("Can't render Window") + SDL_GetError());
    }
    if (!(this->fonts["default"] = TTF_OpenFont("/usr/share/fonts/truetype/DejaVuSans.ttf", STEP))) {
        this->fonts["default"] = TTF_OpenFont("/usr/share/fonts/dejavu/DejaVuSans.ttf", STEP);
    }
}

Sdl2::~Sdl2 ()
{
    for (std::map<std::string, TTF_Font*>::iterator it = this->fonts.begin(); it != this->fonts.end(); ++it) {
        TTF_CloseFont(it->second);
    }
    for (std::map<std::string, SDL_Texture*>::iterator it = this->tex.begin(); it != this->tex.end(); ++it) {
        SDL_DestroyTexture(it->second);
    }
    fonts.clear();
    tex.clear();
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->win);
    TTF_Quit();
    SDL_Quit();
}

void    Sdl2::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(this->win, title.c_str());
}


int Sdl2::eventManagment()
{
    SDL_Event event;

    SDL_PollEvent(&event);
    if (event.key.type != SDL_KEYDOWN)
        return (-1);
    if (this->keyMap[event.key.keysym.scancode])
        return (this->keyMap[event.key.keysym.scancode]);
    return (event.key.keysym.sym);
}

void Sdl2::display(std::stack<AComponent*> components)
{
    SDL_Rect            rect;
    AComponent          *obj;
    GameComponent       *Gobj;
    UIComponent         *Uobj;
    UIAdvanceComponent  *UAobj;
    BackgroundComponent *Bobj;
    HighScoreComponent  *Hobj;
    unsigned int        colorInt;

    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 0);
    SDL_RenderClear(this->render);
    while (!components.empty()) {
        obj = components.top();
        components.pop();
        rect.x = obj->getPos().x * STEP;
        rect.y = obj->getPos().y * STEP;
        if ((Gobj = dynamic_cast<GameComponent*>(obj)) && !Gobj->getSprite2D().empty()) {
            this->displayGame(*Gobj, &rect);
        } else if ((UAobj = dynamic_cast<UIAdvanceComponent*>(obj))) {
            this->displayAdvanceUI(*UAobj, &rect);
        } else if ((Uobj = dynamic_cast<UIComponent*>(obj))) {
            this->displayUI(*Uobj, &rect);
        } else if ((Bobj = dynamic_cast<BackgroundComponent*>(obj))) {
            this->displayBackground(*Bobj, &rect);
        } else if ((Hobj = dynamic_cast<HighScoreComponent*>(obj))) {
            this->displayHighScore(Hobj->getComponentsToDisplay());
        } else {
            rect.w = STEP;
            rect.h = STEP;
            colorInt = this->colors[obj->getColor()];
            SDL_SetRenderDrawColor(this->render, ((colorInt >> 16) & 255), ((colorInt >> 8) & 255), ((colorInt) & 255), ((colorInt >> 24) & 255));
            SDL_RenderFillRect(this->render, &rect);
        }
    }
    SDL_RenderPresent(this->render);
}

void    Sdl2::displayGame(const GameComponent &game, SDL_Rect *rect)
{
    rect->w = game.getDim().x * STEP;
    rect->h = game.getDim().y * STEP;
    if (this->tex[game.getSprite2D()] == 0) {
        this->tex[game.getSprite2D()] = IMG_LoadTexture(this->render,
                std::string("./assets/sprites2D/" + game.getSprite2D()).c_str());
    }
    // SDL_RenderCopy(this->render, this->tex[this->background], NULL, rect);
    SDL_RenderCopy(this->render, this->tex[game.getSprite2D()], NULL, rect);
}

void    Sdl2::displayBackground(const BackgroundComponent &background, SDL_Rect *rect2)
{
    SDL_Rect    rect;

    rect.w = STEP;
    rect.h = STEP;
    this->background = background.getSprite2D();
    if (this->tex[background.getSprite2D()] == 0) {
        this->tex[background.getSprite2D()] = IMG_LoadTexture(this->render,
                std::string("./assets/sprites2D/" + background.getSprite2D()).c_str());
    }
    for (size_t i = 0; i < background.getDim().y; i++) {
        for (size_t j = 0; j < background.getDim().x; j++) {
            rect.x = rect2->x + j * STEP;
            rect.y = rect2->y + i * STEP;
            SDL_RenderCopy(this->render, this->tex[background.getSprite2D()], NULL, &rect);
        }
    }
}

void    Sdl2::displayHighScore(UIComponent const * const *uiComponents)
{
    SDL_Rect    rect;

    for (size_t i = 0; i < HighScoreComponent::componentNb && uiComponents[i] != NULL; i++) {
        rect.x = uiComponents[i]->getPos().x * STEP;
        rect.y = uiComponents[i]->getPos().y * STEP;
        displayUI(*uiComponents[i], &rect);
    }
}

void    Sdl2::displayUI(const UIComponent &ui, SDL_Rect *rect)
{
    unsigned int    colorInt;
    SDL_Color       color;

    if (ui.getText().empty()) {
        return;
    }
    colorInt = this->colors[ui.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    if (!this->fonts["default"]) {
        return;
    }
    this->renderSurface(TTF_RenderText_Blended(this->fonts["default"], ui.getText().c_str(), color), rect);
}

void    Sdl2::displayAdvanceUI(const UIAdvanceComponent &ui, SDL_Rect *rect)
{
    std::string     fontName;
    unsigned int    colorInt;
    SDL_Color       color;

    if (ui.getText().empty()) {
        return;
    }
    colorInt = this->colors[ui.getColor()];
    color.r = ((colorInt) & 255);
    color.g = ((colorInt >> 8) & 255);
    color.b = ((colorInt >> 16) & 255);
    color.a = ((colorInt >> 24) & 255);
    fontName = ui.getFontName();
    if (this->fonts[fontName] == 0) {
        this->fonts[fontName] = TTF_OpenFont(std::string("./assets/fonts/" + fontName + ".ttf").c_str(), ui.getFontSize());
    }
    this->renderSurface(TTF_RenderText_Blended(fonts[fontName], ui.getText().c_str(), color), rect);
}

void    Sdl2::renderSurface(SDL_Surface *surface, SDL_Rect *rect)
{
    SDL_Texture     *texture;

    texture = SDL_CreateTextureFromSurface(this->render, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &(rect->w), &(rect->h));
    rect->x -= rect->w / 2;
    SDL_RenderCopy(this->render, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

void sound()
{
  // Mix
  // if (!SDL_LoadWAV("toto.wav", &have, &audiobuf, &length))
  //   return;

}
