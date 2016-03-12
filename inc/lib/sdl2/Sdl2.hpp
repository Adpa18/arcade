/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Fri Mar 11 21:16:00 2016 Adrien WERY
*/

#ifndef SDL2_HPP_
# define SDL2_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <exception>
# include <stack>
# include <iostream>
# include <map>
# include "IGraph.hpp"
# include "AGame.hpp"
# include "TextComponent.hpp"

class Sdl2 : public IGraph {
private:
    SDL_Window      *win;
    SDL_Renderer    *render;
    std::map<std::string, TTF_Font*> fonts;
    std::map<SDL_Keycode, int>    keyMap = {
        {SDLK_ESCAPE, ESC},
        {SDLK_UP, UP}, {SDLK_DOWN, DOWN}, {SDLK_LEFT, LEFT}, {SDLK_RIGHT, RIGHT}
    };
public:
    Sdl2 (void);
    virtual ~Sdl2 ();

    virtual int     eventManagment();
    virtual void    display(std::stack<AComponent*>);
    virtual void    init(const std::string &name, Vector2 size, std::stack<AComponent*> cache);
    void            affText(const TextComponent &text);

};

extern "C" IGraph *loadLib()
{
    return (new Sdl2());
}


#endif /* !SDL2_HPP_ */
