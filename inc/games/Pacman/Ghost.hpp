#ifndef GHOST_HPP
#define GHOST_HPP

# include "ArcadeSystem.hpp"
# include "GameComponent.hpp"
# include <chrono>
# include <map>

# define WIDTH  50
# define HEIGHT 30
# define STEP	1

enum direction { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, NOTHING };

class Ghost {
public:
    enum state { ALIVE, DEAD, VULNERABLE };
private:
    GameComponent                       *obj;
    AComponent::ComponentColor          first_color;
    Vector2<double>                     startPos;
    state                               status;
    std::map<double, GameComponent*>    &mapObjs;
    direction                           dir;
    bool                                force_dir;
    bool                                slow;
    const std::string                   sprite2D;
public:
    Ghost (std::map<double, GameComponent*> &mapObjs, Vector2<double> pos,
        AComponent::ComponentColor color, const std::string sprite2D);
    virtual ~Ghost ();
    void            goTo(Vector2<double> pos);
    // void            goToRand(Vector2<double> pos);
    GameComponent   *getObj() const;
    state           getState() const;
    Vector2<double> getStartPos() const;
    void            alive();
    void            dead();
    void            vulnerable();
    void            init();
private:
    bool            check(Vector2<double> pos);
    bool			tryMove();
    bool			isInside();
    bool			otherWay();
    void            goToInv(Vector2<double> pos);
    void			inverseDir();
};

#endif /* !GHOST_HPP */
