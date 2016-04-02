#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <stack>
# include <iostream>
# include "AComponent.hpp"
# include "ArcadeSystem.hpp"

class IGame {
public:
    virtual ~IGame() {}
    virtual std::stack<AComponent*> compute(int) = 0;
    virtual void                    restart() = 0;
    virtual std::string const       &getName() const = 0;
    virtual Vector2<double> const   &getSize() const = 0;
};

#endif /* !IGAME_HPP_ */
