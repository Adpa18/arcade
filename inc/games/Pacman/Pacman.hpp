/*
** pacman.hpp for cpp_arcade
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Tue Mar 15 17:55:08 2016 Axel Vencatareddy
** Last update	Wed Mar 16 15:01:11 2016 Axel Vencatareddy
*/

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

# include <vector>
# include <map>
# include "AGame.hpp"
# include "Utils.hpp"
# include "GameComponent.hpp"

# define WIDTH  1000
# define HEIGHT 1000
# define STEP 20
# define PHANTOM 4

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, WAIT };

typedef struct	s_phantom {
  direction	dir;
  GameComponent
}		t_phantom;

class Pacman : public AGame {
private:
    GameComponent			*pacman;
    std::vector<GameComponent*>		phantom;
    std::map<GameComponent*, direction>	dir;
public:
    Pacman ();
    virtual ~Pacman ();
    virtual std::stack<AComponent*>	compute(int);
    virtual std::stack<AComponent*>	getInfos();
    virtual void			restart();
    void				phantom_compute(GameComponent *,
                                        std::stack<AComponent*> &);
    bool				collision();
    bool				limit(Vector2);
    void				newDir(GameComponent *);
    bool				tryLeft(Vector2);
    bool				tryRight(Vector2);
    bool				tryUp(Vector2);
    bool				tryDown(Vector2);
};

extern "C" AGame *loadGame()
{
    return (new Pacman());
}

#endif /* !PACMAN_HPP_ */
