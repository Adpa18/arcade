/*
** pacman.hpp for cpp_arcade
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Tue Mar 15 17:55:08 2016 Axel Vencatareddy
** Last update	Wed Mar 30 19:59:55 2016 Adrien WERY
*/

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"
# include "BackgroundComponent.hpp"
# include "UIComponent.hpp"
# include "AudioComponent.hpp"
# include "ScoreComponent.hpp"
# include "Protocol.hpp"
# include <vector>
# include <map>

# define WIDTH  50
# define HEIGHT 30
# define NB_PH  4

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, NOTHING };

typedef struct	s_phantom {
  direction	dir;
  GameComponent g;
}		t_phantom;

class Pacman : public AGame {
private:
    GameComponent               *pacman;
    std::vector<GameComponent*> phantom;
    std::map<double, GameComponent*> mapObjs;
    direction                   dir;
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
    virtual std::stack<AComponent*>	getInfos();
    virtual void			        restart();
    void 							changeDirection(int key);
    void 							move();
    void 							eat();
private:
    bool                            check(Vector2<double> pos);
    // void				phantom_compute(GameComponent *,
    //                                     std::stack<AComponent*> &);
    // bool				collision();
    // bool				limit(Vector2<double>);
    // void				newDir(GameComponent *);
    // bool				tryLeft(Vector2<double>);
    // bool				tryRight(Vector2<double>);
    // bool				tryUp(Vector2<double>);
    // bool				tryDown(Vector2<double>);
};

extern "C" AGame *loadGame()
{
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
