#ifndef AGAME_HPP_
# define AGAME_HPP_

# include "IGame.hpp"

class AGame : public IGame {
public:
    typedef enum
    {
        ALIVE,
        DEAD
    } GameState;
protected:
    GameState           state;
    const std::string   name;
    Vector2<double>     size;
public:
    AGame(std::string const &name);
    virtual ~AGame();
    virtual std::stack<AComponent*> compute(int) = 0;
    // virtual std::stack<AComponent*> getInfos() const = 0;
    virtual void                    restart() = 0;
    Vector2<double> const           &getSize() const;
    std::string const               &getName() const;
};

#endif /* !AGAME_HPP_ */
