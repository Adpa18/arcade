#ifndef SNAKE_HPP_
#define SNAKE_HPP_

# include <vector>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "AudioComponent.hpp"
# include "HighScoreComponent.hpp"
# include "Protocol.hpp"
# include <string>

# define SIZE   3
# define RANDOM_POS Vector2<double>(rand() % (ArcadeSystem::winWidth - 2) + 1, rand() % (ArcadeSystem::winHeight - 2) + 1)

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN };

class Snake : public AGame {
private:
    std::vector<GameComponent*> snake;
    GameComponent               *target;
    BackgroundComponent         *background;
    std::vector<GameComponent*> walls;
    HighScoreComponent          *highScore;
    UIComponent                 *scoreText;
    direction                   dir;
    size_t                      score;
    // AudioComponent              *sound;
public:
    Snake ();
    virtual ~Snake ();
    virtual std::stack<AComponent*> compute(int key);
    virtual std::stack<AComponent*> getInfos(void) const;
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
