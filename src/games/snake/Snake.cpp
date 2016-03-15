/*
** Snake.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:40:10 2016 Nicolas Constanty
** Last update	Tue Mar 15 21:13:00 2016 Adrien WERY
*/

#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2(WIDTH, HEIGHT))
{
    Vector2 pos(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP);

    this->target = new GameComponent(pos, Vector2(STEP, STEP), YELLOW, NULL, std::string(), std::string());
    this->old_target = new GameComponent(pos, Vector2(STEP, STEP), BLACK, NULL, std::string(), std::string());
    this->restart();
}

Snake::~Snake ()
{}

bool    Snake::check(Vector2 snakePos)
{
    if (snakePos.x < 0 || snakePos.x >= WIDTH || snakePos.y < 0 || snakePos.y >= HEIGHT)
        return (false);
    for (size_t i = 0; i < this->snake.size(); i++) {
        if (snakePos == this->snake[i]->getPos())
            return (false);
    }
    return (true);
}

std::stack<AComponent*>     Snake::compute(int key)
{
    std::stack<AComponent*> components;
    Vector2                 snakePos = this->snake.front()->getPos();
    if (key == LEFT && dir != DIR_RIGHT) {
        dir = DIR_LEFT;
    } else if (key == RIGHT && dir != DIR_LEFT) {
        dir = DIR_RIGHT;
    } else if (key == UP && dir != DIR_DOWN) {
        dir = DIR_UP;
    } else if (key == DOWN && dir != DIR_UP) {
        dir = DIR_DOWN;
    }
    switch (dir) {
        case DIR_LEFT:
            snakePos.x -= STEP;
            break;
        case DIR_RIGHT:
            snakePos.x += STEP;
            break;
        case DIR_UP:
            snakePos.y -= STEP;
            break;
        case DIR_DOWN:
            snakePos.y += STEP;
            break;
    }
    if (!check(snakePos)) {
        this->old_target->setPos(this->target->getPos());
        components.push(this->old_target);
        for (size_t i = 0; i < this->snake.size(); i++) {
            this->snake[i]->setColor(BLACK);
            components.push(this->snake[i]);
        }
        this->restart();
        components.push(this->target);
        return (components);
    }
    this->snake.insert(this->snake.begin(), new GameComponent(snakePos, Vector2(STEP, STEP), CYAN, NULL, std::string(), std::string()));
    for (size_t i = 0; i < this->snake.size(); i++) {
        components.push(this->snake[i]);
    }
    if (this->snake.front()->getPos() == this->target->getPos()) {
        this->target->setPos(Vector2(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
        components.push(this->target);
    } else {
        this->snake.back()->setColor(BLACK);
        this->snake.pop_back();
    }
    return (components);
}

std::stack<AComponent*>     Snake::getInfos()
{
    std::stack<AComponent*> components;

    components.push(this->target);
    return (components);
}

void                        Snake::restart()
{
    this->dir = DIR_UP;
    this->snake.erase(this->snake.begin(), this->snake.end());
    for (size_t i = 0; i < SIZE; i++) {
        this->snake.push_back(new GameComponent(Vector2(WIDTH / 2 , HEIGHT / 2), Vector2(STEP, STEP), CYAN, NULL, std::string(), std::string()));
    }
    this->target->setPos(Vector2(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
}
