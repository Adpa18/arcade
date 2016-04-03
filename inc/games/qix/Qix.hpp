#ifndef QIX_HPP_
# define QIX_HPP_

# include "AGame.hpp"
# include "Vector2.hpp"
# include "GameComponent.hpp"
# include "Protocol.hpp"

class Qix : public AGame {
private:
    GameComponent               *obj;
public:
    Qix ();
    virtual ~Qix ();
    virtual std::stack<AComponent*> compute(int);
    virtual void			        restart();
    void 							changeDirection(int key);
    void                            getMap() const;
    void                            whereAmI() const;
private:
    bool                            check(Vector2<double> objPos);
};

extern "C" void     Play(void);

extern "C" AGame *loadGame()
{
    return (new Qix());
}

#endif /* !QIX_HPP_ */
