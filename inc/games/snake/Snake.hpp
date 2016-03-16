/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:32:51 2016 Nicolas Constanty
** Last update	Wed Mar 16 08:24:11 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"

# define WIDTH  1000
# define HEIGHT 1000
# define STEP   10
# define SIZE   3

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    GameComponent   *old_target;
    GameComponent   *target;
    std::vector<GameComponent*> snake;
    direction       dir;
public:
    Snake ();
    virtual ~Snake ();
    virtual std::stack<AComponent*>   compute(int key);
    virtual std::stack<AComponent*>   getInfos();
    virtual void                      restart();
    bool                              check(Vector2 snakePos);
};

extern "C" AGame *loadGame()
{
    return (new Snake());
}

#endif /* !SNAKE_HPP_ */
