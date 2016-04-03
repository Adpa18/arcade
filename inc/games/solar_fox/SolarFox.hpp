#ifndef SOLAR_FOX_HPP_
# define SOLAR_FOX_HPP_

# include "AGame.hpp"
# include "Vector2.hpp"
# include "GameComponent.hpp"
# include "Protocol.hpp"

class SolarFox : public AGame {
private:
    GameComponent               *obj;
public:
    SolarFox ();
    virtual ~SolarFox ();
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
    return (new SolarFox());
}

#endif /* !SOLAR_FOX_HPP_ */
