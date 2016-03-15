/*
** AGame.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:38:09 2016 Nicolas Constanty
** Last update	Tue Mar 15 19:33:14 2016 Adrien WERY
*/

#ifndef AGAME_HPP_
# define AGAME_HPP_

# include <stack>
# include <iostream>
# include "AComponent.hpp"

enum keys { ESC = 1, UP, DOWN, LEFT, RIGHT };

class AGame {
private:
    std::string name;
    Vector2     size;
public:
    AGame(std::string const &name, Vector2 size);
    virtual ~AGame();
    virtual std::stack<AComponent*> compute(int) = 0;
    virtual std::stack<AComponent*> getInfos() = 0;
    virtual void                    restart() = 0;
    Vector2 const                   &getSize() const;
    std::string const               &getName() const;
};

#endif /* !AGAME_HPP_ */
