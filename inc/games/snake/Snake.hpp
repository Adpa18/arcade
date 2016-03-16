/*
** Snake.hpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:49:30 2016 Adrien WERY
** Last update	Wed Mar 16 22:07:05 2016 Adrien WERY
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "TextComponent.hpp"

# define WIDTH  1000
# define HEIGHT 1000
# define STEP   40
# define SIZE   3

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    AComponent      *old_target;
    GameComponent   *target;
    TextComponent   *scoreText;
    size_t          score;
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
