/*
** AGame.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:38:09 2016 Nicolas Constanty
** Last update	Thu Mar 17 15:09:32 2016 Adrien WERY
*/

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
