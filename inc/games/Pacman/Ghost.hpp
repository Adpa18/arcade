#ifndef GHOST_HPP
#define GHOST_HPP

# include "GameComponent.hpp"
# include <chrono>
# include <map>

# define WIDTH  50
# define HEIGHT 30

class Ghost {
public:
    enum state { ALIVE, DEAD, VULNERABLE };
private:
    GameComponent   *obj;
    Vector2<double> startPos;
    state           status;
    time_t          beginTime;
    std::map<double, GameComponent*> &mapObjs;
public:
    Ghost (std::map<double, GameComponent*> &mapObjs, Vector2<double> pos,
        AComponent::ComponentColor color, const std::string sprite2D);
    virtual ~Ghost ();
    void            goTo(Vector2<double> pos);
    GameComponent   *getObj() const;
    state           getState() const;
    Vector2<double> getStartPos() const;
    void            alive();
    void            dead();
    void            vulnerable();
    void            init();
private:
    bool            check(Vector2<double> pos);
};

#endif /* !GHOST_HPP */
