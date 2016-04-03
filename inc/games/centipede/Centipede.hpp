#ifndef CENTIPEDE_HPP_
# define CENTIPEDE_HPP_

# include "AGame.hpp"
# include "Vector2.hpp"
# include "GameComponent.hpp"
# include "Protocol.hpp"

class Centipede : public AGame {
private:
    GameComponent               *obj;
public:
    Centipede ();
    virtual ~Centipede ();
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
    return (new Centipede());
}

#endif /* !CENTIPEDE_HPP_ */
