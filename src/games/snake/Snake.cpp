/*
** Snake.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:40:10 2016 Nicolas Constanty
** Last update	Tue Mar 15 15:47:27 2016 Adrien WERY
*/

#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2(1000, 1000))
{
    this->target = new GameComponent(Vector2(rand() % 100 * STEP, rand() % 100 * STEP), NULL, std::string(), std::string());
    this->snake = new GameComponent(Vector2(rand() % 100 * STEP, rand() % 100 * STEP), NULL, std::string(), std::string());
}

Snake::~Snake ()
{}

std::stack<AComponent*>     Snake::compute(int key)
{
    std::stack<AComponent*> components;
    Vector2                 snakePOS = this->snake->getPos();
    switch (key) {
        case LEFT:
            snakePOS.x -= STEP;
            break;
        case RIGHT:
            snakePOS.x += STEP;
            break;
        case UP:
            snakePOS.y -= STEP;
            break;
        case DOWN:
            snakePOS.y += STEP;
            break;
    }
    this->snake->setPos(snakePOS);
    components.push(this->snake);
    return (components);
}

std::stack<AComponent*>     Snake::getInfos()
{
    std::stack<AComponent*> components;

    components.push(this->target);
    components.push(this->snake);
    return (components);
}

void                        Snake::restart()
{

}
