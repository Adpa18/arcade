/*
** Snake.hpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:49:30 2016 Adrien WERY
** Last update	Thu Mar 17 04:20:13 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "TextComponent.hpp"
# include "AudioComponent.hpp"

# define WIDTH  50
# define HEIGHT 30
# define STEP   1
# define SIZE   3

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    // AComponent      *old_target;
    GameComponent   *target;
    TextComponent   *scoreText;
    AudioComponent  *sound;
    size_t          score;
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
    bool                            check(Vector2 snakePos);
    const   std::string             getImg(size_t pos);

};

extern "C" AGame *loadGame()
{
    return (new Snake());
}

#endif /* !SNAKE_HPP_ */
