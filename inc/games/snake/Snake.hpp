/*
** Snake.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:33:57 2016 Nicolas Constanty
** Last update	Wed Mar 16 21:33:59 2016 Nicolas Constanty
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"

# define WIDTH  1000
# define HEIGHT 1000
# define STEP   20
# define SIZE   10

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
