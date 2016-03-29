/*
** Snake.hpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:49:30 2016 Adrien WERY
** Last update	Mon Mar 28 21:31:35 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "AudioComponent.hpp"
# include "ScoreComponent.hpp"

# define WIDTH  50
# define HEIGHT 30
# define STEP   1
# define SIZE   3

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    AComponent      *old_target;
    GameComponent   *target;
    ScoreComponent  *score;
    AudioComponent  *sound;
    std::vector<GameComponent*> snake;
    BackgroundComponent *background;
    direction       dir;
    std::vector<std::string>    backgroundSprites;
public:
    Snake ();
    virtual ~Snake ();
    virtual std::stack<AComponent*> compute(int key);
    virtual std::stack<AComponent*> getInfos();
    virtual void                    restart();
    bool                            check(Vector2<double> snakePos);
    const   std::string             getImg(size_t pos);

};

extern "C" AGame *loadGame()
{
    return (new Snake());
}

#endif /* !SNAKE_HPP_ */
