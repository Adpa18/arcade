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
# include "GameComponent.hpp"
# include "UIComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "UIAdvanceComponent.hpp"
# include "HighScoreComponent.hpp"

# define STEP 30

class Sdl2 : public IGraph {
private:
    SDL_Window      *win;
    SDL_Renderer    *render;
    Vector2<double> size;
    std::string     background;

    std::map<std::string, TTF_Font*> fonts;
    std::map<std::string, SDL_Texture*> tex;
    std::map<int, int>    keyMap = {
        {SDL_SCANCODE_ESCAPE, ArcadeSystem::Exit},
        {SDL_SCANCODE_UP, ArcadeSystem::ArrowUp},
        {SDL_SCANCODE_DOWN, ArcadeSystem::ArrowDown},
        {SDL_SCANCODE_LEFT, ArcadeSystem::ArrowLeft},
        {SDL_SCANCODE_RIGHT, ArcadeSystem::ArrowRight},
        {SDL_SCANCODE_2, ArcadeSystem::PrevGraph},
        {SDL_SCANCODE_3, ArcadeSystem::NextGraph},
        {SDL_SCANCODE_4, ArcadeSystem::NextGame},
        {SDL_SCANCODE_5, ArcadeSystem::NextGame},
        {SDL_SCANCODE_8, ArcadeSystem::Restart},
        {SDL_SCANCODE_9, ArcadeSystem::Home},
        {SDL_SCANCODE_P, ArcadeSystem::Pause},
        {SDL_SCANCODE_RETURN, ArcadeSystem::Enter},
        {SDL_SCANCODE_BACKSPACE, ArcadeSystem::Backspace}
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
public:
    Sdl2 (void);
    virtual ~Sdl2 ();

    virtual int     eventManagment();
    virtual void    display(std::stack<AComponent*>);
    // virtual void    init(const std::string &name);
    // virtual void    init(const std::string &name, std::stack<AComponent*> cache);
    virtual void    setTitle(const std::string &title);

private:
    void            displayGame(const GameComponent &game, SDL_Rect *rect);
    void            displayUI(const UIComponent &ui, SDL_Rect *rect);
    void            displayAdvanceUI(const UIAdvanceComponent &ui, SDL_Rect *rect);
    void            displayBackground(const BackgroundComponent &background, SDL_Rect *rect);
    void            displayHighScore(UIComponent const * const *uiComponents);
    void			fill_audio(void *udata, Uint8 *stream, int len);
    void            renderSurface(SDL_Surface *surface, SDL_Rect *rect);

};

extern "C" IGraph *loadLib()
{
    return (new Sdl2());
}

#endif /* !SDL2_HPP_ */
