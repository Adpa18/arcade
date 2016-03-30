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
# include "Protocol.hpp"

# define WIDTH  50
# define HEIGHT 30
# define SIZE   3

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    GameComponent   *target;
    ScoreComponent  *score;
    AudioComponent  *sound;
    std::vector<GameComponent*> snake;
    BackgroundComponent *background;
    std::vector<std::string>    backgroundSprites;
    std::vector<GameComponent*> walls;
    direction       dir;
public:
    Snake ();
    virtual ~Snake ();
    virtual std::stack<AComponent*> compute(int key);
    virtual std::stack<AComponent*> getInfos(void);
    virtual void                    restart(void);
    void                            Play(void);
    void                            getMap();
    void                            whereAmI();
    void 							changeDirection(int key);
private:
    bool                            check(Vector2<double> snakePos);
    const   std::string             getImg(size_t pos);

};

extern "C" void     Play(void);

extern "C" AGame *loadGame()
{
    return (new Snake());
}

#endif /* !SNAKE_HPP_ */
