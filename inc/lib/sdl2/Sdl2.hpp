/*
** Ncurses.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 21:25:48 2016 Nicolas Constanty
** Last update	Fri Mar 11 18:22:02 2016 Adrien WERY
*/

#ifndef SDL2_HPP_
# define SDL2_HPP_

# include <SDL2/SDL.h>
# include <exception>
# include <stack>
# include <iostream>
# include "IGraph.hpp"


class Sdl2 : public IGraph {
private:
    SDL_Window  *win;
public:
    Sdl2 (void);
    virtual ~Sdl2 ();


    virtual int   eventManagment();
    virtual void  display(std::stack<AComponent*>);
    virtual void  init(const std::string &name, Vector2 size, std::stack<AComponent*> cache);

};

extern "C" IGraph *loadLib()
{
    return (new Sdl2());
}


#endif /* !SDL2_HPP_ */
