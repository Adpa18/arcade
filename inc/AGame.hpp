#ifndef AGAME_HPP_
# define AGAME_HPP_

# include <stack>
# include <iostream>
# include "AComponent.hpp"

enum keys { ESC = 1, UP, DOWN, LEFT, RIGHT,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9};

class AGame {
private:
    std::string name;
    Vector2<int>     size;
public:
    AGame(std::string const &name, Vector2<int> size);
    virtual ~AGame();
    virtual std::stack<AComponent*> compute(int) = 0;
    virtual std::stack<AComponent*> getInfos() = 0;
    virtual void                    restart() = 0;
    Vector2<int> const                   &getSize() const;
    std::string const               &getName() const;
};

#endif /* !AGAME_HPP_ */
