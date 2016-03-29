#ifndef OpenGL_HPP_
# define OpenGL_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <cstdlib>
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

class OpenGL : public IGraph {
private:
    SDL_Window      *win;
    SDL_GLContext   gl;
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
    std::map<AComponent::ComponentColor, int>    colors = {
        {AComponent::BLACK, 0x000000},
        {AComponent::RED, 0xFF0000},
        {AComponent::GREEN, 0x00FF00},
        {AComponent::BLUE, 0x0000FF},
        {AComponent::YELLOW, 0xFFFF00},
        {AComponent::MAGENTA, 0xFF00FF},
        {AComponent::CYAN, 0x00FFFF},
        {AComponent::WHITE, 0xFFFFFF}
    };
    std::map<size_t, SDL_Surface *> texts;

    Vector2<double>         size;
    std::string     background;
    bool						is_init;
    bool						is_destroy;
public:
    OpenGL (void);
    virtual ~OpenGL ();

    virtual int     eventManagment();
    virtual void    display(std::stack<AComponent*>);
    virtual void    init(const std::string &name, Vector2<double> size, std::stack<AComponent*> cache);
    virtual void    init(const std::string &name, Vector2<double> size);
    virtual void    destroy();

private:
    void            drawCube(Vector2<double> pos, Vector2<double> size, Vector2<double> rot);
    void            displayGame(const GameComponent &game);
    void            displayUI(const UIComponent &ui);
    void            displayBackground(const BackgroundComponent &background);
    void			fill_audio(void *udata, Uint8 *stream, int len);

};

extern "C" IGraph *loadLib()
{
    return (new OpenGL());
}

extern "C" void initLib(IGraph *graph, const std::string &name, Vector2<double> size, std::stack<AComponent *> cache)
{
  static_cast<OpenGL *>(graph)->init(name, size, cache);
}

extern "C" void destroyLib(IGraph *graph)
{
  static_cast<OpenGL *>(graph)->destroy();
}


#endif /* !OpenGL_HPP_ */
