/*
** Snake.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:47:41 2016 Adrien WERY
** Last update	Thu Mar 17 03:39:05 2016 Nicolas Constanty
*/

#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2(WIDTH, HEIGHT))
{
    Vector2 pos(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP);
    this->target = new GameComponent(pos, Vector2(STEP, STEP), RED, ' ', "snakeApple.png", NULL);
    this->old_target = new GameComponent(pos, Vector2(STEP, STEP), BLACK, ' ', "snakeBackground1.jpg", NULL);
    this->scoreText = new TextComponent(Vector2(1, 1), Vector2(50, 5), WHITE, "", "frenchy", 60);
    this->sound = new AudioComponent(Vector2(0, 0), BLACK, '\a', "", "");
    this->restart();
}

Snake::~Snake ()
{}

const   std::string     Snake::getImg(size_t pos)
{
    std::string     img = "snake";

    if (pos == 0) {
        img += "Head";
        if (this->dir == DIR_LEFT) {
            img += "L";
        } else if (this->dir == DIR_RIGHT) {
            img += "R";
        } else if (this->dir == DIR_UP) {
            img += "T";
        } else if (this->dir == DIR_DOWN) {
            img += "B";
        }
    } else if (pos == this->snake.size() - 1) {
        Vector2 pos0 = this->snake[pos]->getPos();
        Vector2 pos1 = this->snake[pos - 1]->getPos();
        img += "Tail";
        if (pos0.x == pos1.x - STEP) {
            img += "L";
        } else if (pos0.x == pos1.x + STEP) {
            img += "R";
        } else if (pos0.y == pos1.y - STEP) {
            img += "T";
        } else if (pos0.y == pos1.y + STEP) {
            img += "B";
        }
    } else {
        Vector2 pos0 = this->snake[pos]->getPos();
        Vector2 pos1 = this->snake[pos - 1]->getPos();
        Vector2 pos2 = this->snake[pos + 1]->getPos();
        if ((pos0.x == pos1.x + STEP && pos0.x == pos2.x - STEP)
            || (pos0.x == pos1.x - STEP && pos0.x == pos2.x + STEP)) {
            img += "H";
        } else if ((pos0.y == pos1.y + STEP && pos0.y == pos2.y - STEP)
            || (pos0.y == pos1.y - STEP && pos0.y == pos2.y + STEP)) {
                img += "V";
        } else {
            if (pos0.x == pos1.x + STEP || pos0.x == pos2.x + STEP) {
                img += "Left";
            } else {
                img += "Right";
            }
            if (pos0.y == pos1.y + STEP || pos0.y == pos2.y + STEP) {
                img += "Top";
            } else {
                img += "Bottom";
            }
        }
    }
    img += ".png";
    return (img);
}

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
            this->snake[i]->setSprite2D("snakeBackground1.jpg");
            components.push(this->snake[i]);
        }
        this->restart();
        components.push(this->sound);
        components.push(this->target);
        return (components);
    }
    this->snake.insert(this->snake.begin(), new GameComponent(snakePos, Vector2(STEP, STEP), GREEN, ' ', "", NULL));
    components.push(this->scoreText);
    if (this->snake.front()->getPos() == this->target->getPos()) {
        this->target->setPos(Vector2(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
        components.push(this->target);
        components.push(this->sound);
        ++this->score;
        this->scoreText->setText("Score : " + std::to_string(this->score));
    } else {
        this->snake.back()->setColor(BLACK);
        this->snake.back()->setSprite2D("snakeBackground1.jpg");
        components.push(this->snake.back());
        this->snake.pop_back();
    }
    for (size_t i = 0; i < this->snake.size(); i++) {
        this->snake[i]->setSprite2D(this->getImg(i));
        components.push(this->snake[i]);
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
    this->score = 0;
    this->scoreText->setText("Score : 0");
    this->snake.erase(this->snake.begin(), this->snake.end());
    for (size_t i = 0; i < SIZE; i++) {
        this->snake.push_back(new GameComponent(Vector2(WIDTH / STEP / 2 * STEP , HEIGHT / STEP / 2 * STEP), Vector2(STEP, STEP), RED, ' ', "", NULL));
    }
    this->target->setPos(Vector2(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
}
