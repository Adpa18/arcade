#ifndef SDL2_HPP_
# define SDL2_HPP_

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include <exception>
# include <stack>
# include <iostream>
# include <map>
# include "IGraph.hpp"
# include "AGame.hpp"
# include "GameComponent.hpp"
# include "UIComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"


# define STEP 30

class Sdl2 : public IGraph {
private:
    SDL_Window      *win;
    SDL_Renderer    *render;
    std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, SDL_Texture*> tex;
    std::map<SDL_Keycode, int>    keyMap = {
        {SDL_SCANCODE_ESCAPE, ESC}, {SDL_SCANCODE_UP, UP}, {SDL_SCANCODE_DOWN, DOWN},
        {SDL_SCANCODE_LEFT, LEFT}, {SDL_SCANCODE_RIGHT, RIGHT},
        {SDL_SCANCODE_0, KEY_0}, {SDL_SCANCODE_1, KEY_1}, {SDL_SCANCODE_2, KEY_2},
        {SDL_SCANCODE_3, KEY_3}, {SDL_SCANCODE_4, KEY_4}, {SDL_SCANCODE_5, KEY_5},
        {SDL_SCANCODE_6, KEY_6}, {SDL_SCANCODE_7, KEY_7}, {SDL_SCANCODE_8, KEY_8},
        {SDL_SCANCODE_9, KEY_9}
    };
    std::map<ComponentColor, int>    colors = {
        {BLACK, 0x000000},
        {RED, 0xFF0000},
        {GREEN, 0x00FF00},
        {BLUE, 0x0000FF},
        {YELLOW, 0xFFFF00},
        {MAGENTA, 0xFF00FF},
        {CYAN, 0x00FFFF},
        {WHITE, 0xFFFFFF}
    };
    Vector2<int>         size;
    std::string     background;
    bool						is_init;
    bool						is_destroy;
public:
    Sdl2 (void);
    virtual ~Sdl2 ();

    virtual int     eventManagment();
    virtual void    display(std::stack<AComponent*>);
    virtual void    init(const std::string &name, Vector2<int> size, std::stack<AComponent*> cache);
    virtual void    init(const std::string &name, Vector2<int> size);
    virtual void    destroy();

private:
    void            displayGame(const GameComponent &game, SDL_Rect *rect);
    void            displayUI(const UIComponent &ui, SDL_Rect *rect);
    void            displayBackground(const BackgroundComponent &background, SDL_Rect *rect);
    void			      fill_audio(void *udata, Uint8 *stream, int len);

};

extern "C" IGraph *loadLib()
{
    return (new Sdl2());
}

extern "C" void initLib(IGraph *graph, const std::string &name, Vector2<int> size, std::stack<AComponent *> cache)
{
  static_cast<Sdl2 *>(graph)->init(name, size, cache);
}

extern "C" void destroyLib(IGraph *graph)
{
  static_cast<Sdl2 *>(graph)->destroy();
}

#endif /* !SDL2_HPP_ */
