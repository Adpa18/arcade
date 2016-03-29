/*
** Snake.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:47:41 2016 Adrien WERY
** Last update	Mon Mar 28 21:31:39 2016 Nicolas Constanty
*/

#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2<int>(WIDTH, HEIGHT))
{
    Vector2<int> pos(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP);
    this->target = new GameComponent(pos, Vector2<int>(STEP, STEP), RED, ' ', "snakeApple.png", NULL);
    this->background = new BackgroundComponent(Vector2<int>(0, 0), Vector2<int>(WIDTH, HEIGHT), BLACK, "");
    this->sound = new AudioComponent(Vector2<int>(0, 0), BLACK, '\a', "", "");
    this->old_target = new GameComponent(pos, Vector2<int>(STEP, STEP), BLACK, ' ', this->background->getSprite2D(), NULL);
    this->score = new ScoreComponent("snake");
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
        Vector2<int> pos0 = this->snake[pos]->getPos();
        Vector2<int> pos1 = this->snake[pos - 1]->getPos();
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
        Vector2<int> pos0 = this->snake[pos]->getPos();
        Vector2<int> pos1 = this->snake[pos - 1]->getPos();
        Vector2<int> pos2 = this->snake[pos + 1]->getPos();
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

bool    Snake::check(Vector2<int> snakePos)
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
    Vector2<int>                 snakePos = this->snake.front()->getPos();

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
        components.push(this->target);
        components.push(this->background);
        components.push(this->old_target);
        for (size_t i = 0; i < this->snake.size(); i++) {
            this->snake[i]->setColor(BLACK);
            this->snake[i]->setSprite2D(this->background->getSprite2D());
            components.push(this->snake[i]);
        }
        components.push(this->sound);
        this->restart();
        return (components);
    }
    this->snake.insert(this->snake.begin(), new GameComponent(snakePos, Vector2<int>(STEP, STEP), GREEN, ' ', "", NULL));
    components.push(this->score->getScoreUI());
    if (this->snake.front()->getPos() == this->target->getPos()) {
        this->target->setPos(Vector2<int>(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
        components.push(this->target);
        components.push(this->sound);
        this->score->setScore(this->score->getScore() + 10);
        components.push(new BackgroundComponent(this->score->getScoreUI()->getPos(),
            this->score->getScoreUI()->getSize(), BLACK, this->background->getSprite2D()));
        this->score->getScoreUI()->setText("Score : " + std::to_string(this->score->getScore()));
    } else {
        this->snake.back()->setColor(BLACK);
        this->snake.back()->setSprite2D(this->background->getSprite2D());
        components.push(this->snake.back());
        this->snake.pop_back();
    }
    for (size_t i = 0; i < this->snake.size(); i++) {
        this->snake[i]->setSprite2D(this->getImg(i));
        components.push(this->snake[i]);
    }
    components.push(this->target);
    components.push(this->background);
    return (components);
}

std::stack<AComponent*>     Snake::getInfos()
{
    std::stack<AComponent*> components;

    components.push(this->target);
    components.push(this->background);
    return (components);
}

void                        Snake::restart()
{
    static const char * const backgroundSprites[] = {
        "snakeBackground.jpg",
        "snakeBackground1.jpg",
        "snakeBackground2.jpg"
    };
    this->dir = DIR_UP;
    this->score->writeScore();
    this->background->setSprite2D(backgroundSprites[rand() % 3]);
    this->score->getScoreUI()->setText("Score : 0");
    this->snake.erase(this->snake.begin(), this->snake.end());
    for (size_t i = 0; i < SIZE; i++) {
      this->snake.push_back(new GameComponent(Vector2<int>(WIDTH / STEP / 2 * STEP, HEIGHT / STEP / 2 * STEP), Vector2<int>(STEP, STEP), RED, ' ', "", NULL));
    }
    this->target->setPos(Vector2<int>(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
}
