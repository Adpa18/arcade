#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "AudioComponent.hpp"
# include "HighScoreComponent.hpp"
# include "Protocol.hpp"
# include "Ghost.hpp"
# include <vector>
# include <map>
# include <cmath>

# define NB_PH  4
# define STEP   1

enum state { ON_GAME, ON_PAUSE, ON_START };

class Pacman : public AGame {
private:
    GameComponent               *pacman;
    std::vector<Ghost*>         ghosts;
    std::map<double, GameComponent*> mapObjs;
    direction                   dir;
    enum state						play_state;
    const char                  map[HEIGHT + 1][WIDTH + 1] = {
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
        "Xo.....................XXXX.....................oX",
        "X.XXXXXXXX.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.XXXXXXXX.X",
        "X.X      X.X         X.XXXX.X         X.X      X.X",
        "X.XXXXXXXX.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.XXXXXXXX.X",
        "X................................................X",
        "X.XXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXX.X",
        "X.XXXXXXXX.X  X.XXXXXXXX  XXXXXXXX.X  X.XXXXXXXX.X",
        "X..........X  X........X  X........X  X..........X",
        "XXXXXXXXXX.X  XXXXXXXX.X  X.XXXXXXXX  X.XXXXXXXXXX",
        "       XXX.X  XXXXXXXX.XXXX.XXXXXXXX  X.XXX       ",
        "       XXX.X  X....................X  X.XXX       ",
        "       XXX.X  X.XXXXX.XXX XXX.XXXX.X  X.XXX       ",
        "XXXXXXXXXX.XXXX.X   X.X     X.X  X.XXXX.XXXXXXXXXX",
        "          ......X   X.X     X.X  X......          ",
        "XXXXXXXXXX.XXXX.X   X.X     X.X  X.XXXX.XXXXXXXXXX",
        "       XXX.X  X.X   X.X     X.X  X.X  X.XXX       ",
        "       XXX.X  X.XXXXX.XXXXXXX.XXXX.X  X.XXX       ",
        "       XXX.X  X....................X  X.XXX       ",
        "XXXXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXXXX",
        "X......................X  X......................X",
        "X.XXXXXXXX.XXXXXXXXXXX.X  X.XXXXXXXXXXX.XXXXXXXX.X",
        "X.XXXX   X.XXXXXXXXXXX.XXXX.XXXXXXXXXXX.X   XXXX.X",
        "X....X   X..............................X   X....X",
        "XXXX.X   X.XXXX.XXXXXXXXXXXXXXXXXX.XXXX.X   X.XXXX",
        "XXXX.XXXXX.X  X.XXXXXXXX  XXXXXXXX.X  X.XXXXX.XXXX",
        "X..........X  X........X  X........X  X..........X",
        "X.XXXXXXXXXXXXXXXXXXXX.XXXX.XXXXXXXXXXXXXXXXXXXX.X",
        "Xo..............................................oX",
        "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"};
public:
    Pacman ();
    virtual ~Pacman ();
    virtual std::stack<AComponent*> compute(int);
    virtual std::stack<AComponent*>	getInfos() const;
    virtual void			        restart();
    void 							changeDirection(int key);
    void 							move();
    void 							eat();
private:
    bool                            check(Vector2<double> pos);
    bool							is_empty();
};

extern "C" AGame *loadGame()
{
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
