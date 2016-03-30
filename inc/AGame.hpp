#ifndef AGAME_HPP_
# define AGAME_HPP_

# include <stack>
# include <iostream>
# include "AComponent.hpp"
# include "ArcadeSystem.hpp"

class AGame {
private:
    std::string name;
    Vector2<double>     size;
public:
    AGame(std::string const &name, Vector2<double> size);
    virtual ~AGame();
    virtual std::stack<AComponent*> compute(int) = 0;
    virtual std::stack<AComponent*> getInfos() = 0;
    virtual void                    restart() = 0;
    Vector2<double> const                   &getSize() const;
    std::string const               &getName() const;
};

#endif /* !AGAME_HPP_ */
