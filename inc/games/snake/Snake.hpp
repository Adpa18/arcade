/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:32:51 2016 Nicolas Constanty
** Last update	Tue Mar 15 15:40:41 2016 Adrien WERY
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"

# define STEP 10

class Snake : public AGame {
private:
    GameComponent   *target;
    GameComponent   *snake;
public:
    Snake ();
    virtual ~Snake ();
    virtual std::stack<AComponent*>   compute(int key);
    virtual std::stack<AComponent*>   getInfos();
    virtual void                      restart();
};

extern "C" AGame *loadGame()
{
    return (new Snake());
}

#endif /* !SNAKE_HPP_ */
