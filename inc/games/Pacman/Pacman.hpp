#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include "AGame.hpp"
# include "Vector2.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "HighScoreComponent.hpp"
# include "Protocol.hpp"
# include "Ghost.hpp"
# include <vector>
# include <map>
# include <cmath>

# define NB_PH  4
# define STEP   1

enum p_state { ON_GAME, ON_PAUSE, ON_START };
enum e_state { INVINCIBLE, NORMAL };

class Pacman : public AGame {
private:
    GameComponent               *pacman;
    std::vector<Ghost*>         ghosts;
    std::map<double, GameComponent*> mapObjs;
    direction                   dir;
    time_t						beginTime;
    enum p_state				play_state;
    enum e_state				eat_state;
    int							nb_life;
    const char                  map[ArcadeSystem::winHeight + 1][ArcadeSystem::winWidth + 1] = {
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "X..........X..........................X..........X",
        "X.XXXXXXXX.X.XXXXXXXXXXXXXXXXXXXXXXXX.X.XXXXXXXX.X",
        "X.Xo.......X............XX............X.......oX.X",
        "X.X.XXXXXX.X.XXXXXXXXXX.XX.XXXXXXXXXX.X.XXXXXX.X.X",
        "X.X.XXXXXX.X.X        X.XX.X        X.X.XXXXXX.X.X",
        "X.X.XXXXXX.X.X        X.XX.X        X.X.XXXXXX.X.X",
        "X.X........X.X        X.XX.X        X.X........X.X",
        "X.XXXXXXXX.X.X        X.XX.X        X.X.XXXXXXXX.X",
        "X..........X.XXXXXXXXXX.XX.XXXXXXXXXX.X..........X",
        "XXXXXXXXXX...........XX.XX.XX...........XXXXXXXXXX",
        " .......XX.XXXXXXXXX..........XXXXXXXXX.XX....... ",
        "XXXXXXX.XX.........X.XXXX XXX.X.........XX.XXXXXXX",
        " .......XX.XXXXXXX.X.X      X.X.XXXXXXX.XX....... ",
        "XXXXXXX....X     X.X.X      X.X.X     X....XXXXXXX",
        "X....XX.XX.X     X.X.X      X.X.X     X.XX.XX....X",
        "X.XX.XX.XX.XXXXXXX.X.X      X.X.XXXXXXX.XX.XX.XX.X",
        "X.XX.XX.XX.........X.XXXXXXXX.X.........XX.XX.XX.X",
        "X.XX.XX....X.XXXXXXX..........XXXXXXX.X....XX.XX.X",
        "X.XX.XXXXX.X.........XX.XX.XX.........X.XXXXX.XX.X",
        "X..........X.XXXXXXXXXX.XX.XXXXXXXXXX.X..........X",
        "X.XXXXXXXX.X.X        X.XX.X        X.X.XXXXXXXX.X",
        "X.X........X.X        X.XX.X        X.X........X.X",
        "X.X.XXXXXX.X.X        X.XX.X        X.X.XXXXXX.X.X",
        "X.X.XXXXXX.X.X        X.XX.X        X.X.XXXXXX.X.X",
        "X.X.XXXXXX.X.XXXXXXXXXX.XX.XXXXXXXXXX.X.XXXXXX.X.X",
        "X.Xo.......X............XX............X.......oX.X",
        "X.XXXXXXXX.X.XXXXXXXXXXXXXXXXXXXXXXXX.X.XXXXXXXX.X",
        "X..........X..........................X..........X",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"};
public:
    Pacman ();
    virtual ~Pacman ();
    virtual std::stack<AComponent*> compute(int);
    // virtual std::stack<AComponent*>	getInfos() const;
    virtual void			        restart();
    void							restart_with_life();
    void 							changeDirection(int key);
    void                            getMap() const;
    void                            whereAmI() const;
    void 							move();
    void 							eat();
private:
    bool                            check(Vector2<double> pos);
    bool							is_empty();
};

extern "C" void     Play(void);

extern "C" AGame *loadGame()
{
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
