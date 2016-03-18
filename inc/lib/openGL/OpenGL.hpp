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
        {SDLK_ESCAPE, ESC},
        {SDLK_UP, UP}, {SDLK_DOWN, DOWN}, {SDLK_LEFT, LEFT}, {SDLK_RIGHT, RIGHT},
        {SDLK_0, KEY_0}, {SDLK_F1, KEY_1}, {SDLK_F2, KEY_2}, {SDLK_F3, KEY_3},
        {SDLK_F4, KEY_4}, {SDLK_F5, KEY_5}, {SDLK_F6, KEY_6}, {SDLK_F7, KEY_7},
        {SDLK_F8, KEY_8}, {SDLK_F9, KEY_9}
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
    std::map<size_t, SDL_Surface *> texts;

    Vector2         size;
    std::string     background;
public:
    OpenGL (void);
    virtual ~OpenGL ();

    virtual int     eventManagment();
    virtual void    display(std::stack<AComponent*>);
    virtual void    init(const std::string &name, Vector2 size, std::stack<AComponent*> cache);
    virtual void    destroy();

private:
    void            drawCube(Vector2 pos, Vector2 size, Vector2 rot);
    void            displayGame(const GameComponent &game);
    void            displayUI(const UIComponent &ui);
    void            displayBackground(const BackgroundComponent &background);
    void			fill_audio(void *udata, Uint8 *stream, int len);

};

extern "C" IGraph *loadLib()
{
    return (new OpenGL());
}


#endif /* !OpenGL_HPP_ */
