#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2<double>(WIDTH, HEIGHT))
{
    Vector2<double> pos(rand() % ((WIDTH - 1) / STEP) * STEP + STEP, rand() % ((HEIGHT - 1) / STEP) * STEP + STEP);

    this->target = new GameComponent(pos, Vector2<double>(STEP, STEP), AComponent::RED, ' ', "snakeApple.png", GameComponent::CUBE_LARGE);
    this->background = new BackgroundComponent(Vector2<double>(0, 0), Vector2<double>(WIDTH, HEIGHT), AComponent::BLACK, "");
    this->sound = new AudioComponent(Vector2<double>(0, 0), AComponent::BLACK, '\a', "", "");
    this->old_target = new GameComponent(pos, Vector2<double>(STEP, STEP), AComponent::BLACK, ' ', this->background->getSprite2D(), GameComponent::CUBE_LARGE);
    this->score = new ScoreComponent("snake");
    for (size_t i = 0; i < WIDTH; i += STEP) {
        this->walls.push_back(new GameComponent(Vector2<double>(i, 0), Vector2<double>(STEP, STEP), AComponent::YELLOW, ' ', "", GameComponent::CUBE_LARGE));
        this->walls.push_back(new GameComponent(Vector2<double>(i, HEIGHT - 1), Vector2<double>(STEP, STEP), AComponent::YELLOW, ' ', "", GameComponent::CUBE_LARGE));
    }
    for (size_t i = 0; i < HEIGHT; i += STEP) {
        this->walls.push_back(new GameComponent(Vector2<double>(0, i), Vector2<double>(STEP, STEP), AComponent::YELLOW, ' ', "", GameComponent::CUBE_LARGE));
        this->walls.push_back(new GameComponent(Vector2<double>(WIDTH - 1, i), Vector2<double>(STEP, STEP), AComponent::YELLOW, ' ', "", GameComponent::CUBE_LARGE));
    }
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
        Vector2<double> pos0 = this->snake[pos]->getPos();
        Vector2<double> pos1 = this->snake[pos - 1]->getPos();
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
        Vector2<double> pos0 = this->snake[pos]->getPos();
        Vector2<double> pos1 = this->snake[pos - 1]->getPos();
        Vector2<double> pos2 = this->snake[pos + 1]->getPos();
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

bool    Snake::check(Vector2<double> snakePos)
{
    if (snakePos.x < 1 || snakePos.x >= WIDTH - 1 || snakePos.y < 1 || snakePos.y >= HEIGHT - 1)
        return (false);
    for (size_t i = 0; i < this->snake.size(); i++) {
        if (snakePos == this->snake[i]->getPos())
            return (false);
    }
    return (true);
}

void 		Snake::changeDirection(int key)
{
    if (key == ArcadeSystem::ArrowLeft && this->dir != DIR_RIGHT) {
        this->dir = DIR_LEFT;
    } else if (key == ArcadeSystem::ArrowRight && this->dir != DIR_LEFT) {
        this->dir = DIR_RIGHT;
    } else if (key == ArcadeSystem::ArrowUp && this->dir != DIR_DOWN) {
        this->dir = DIR_UP;
    } else if (key == ArcadeSystem::ArrowDown && this->dir != DIR_UP) {
        this->dir = DIR_DOWN;
    }
}

std::stack<AComponent*>     Snake::compute(int key)
{
    std::stack<AComponent*> components;
    Vector2<double>                 snakePos = this->snake.front()->getPos();

    this->changeDirection(key);
    switch (this->dir) {
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
            this->snake[i]->setColor(AComponent::BLACK);
            this->snake[i]->setSprite2D(this->background->getSprite2D());
            components.push(this->snake[i]);
        }
        components.push(this->sound);
        this->restart();
        return (components);
    }
    this->snake.insert(this->snake.begin(), new GameComponent(snakePos, Vector2<double>(STEP, STEP), AComponent::GREEN, ' ', "", GameComponent::CUBE_LARGE));
    components.push(this->score->getScoreUI());
    if (this->snake.front()->getPos() == this->target->getPos()) {
        this->target->setPos(Vector2<double>(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
        components.push(this->target);
        components.push(this->sound);
        this->score->setScore(this->score->getScore() + 10);
        components.push(new BackgroundComponent(this->score->getScoreUI()->getPos(),
            this->score->getScoreUI()->getDim(), AComponent::BLACK, this->background->getSprite2D()));
        this->score->getScoreUI()->setText("Score : " + std::to_string(this->score->getScore()));
    } else {
        // this->snake.back()->setColor(AComponent::BLACK);
        // this->snake.back()->setSprite2D(this->background->getSprite2D());
        // components.push(this->snake.back());
        this->snake.pop_back();
    }
    for (size_t i = 0; i < this->snake.size(); i++) {
        this->snake[i]->setSprite2D(this->getImg(i));
        components.push(this->snake[i]);
    }
    for (size_t i = 0; i < this->walls.size(); i++) {
        components.push(this->walls[i]);
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
      this->snake.push_back(new GameComponent(Vector2<double>(WIDTH / STEP / 2 * STEP, HEIGHT / STEP / 2 * STEP), Vector2<double>(STEP, STEP), AComponent::RED, ' ', "", GameComponent::CUBE_LARGE));
    }
    this->target->setPos(Vector2<double>(rand() % (WIDTH / STEP) * STEP, rand() % (HEIGHT / STEP) * STEP));
}

void        Snake::updateMap(struct arcade::GetMap *map)
{
    for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
        if (this->target->getPos().y * WIDTH + this->target->getPos().x == i) {
            map->tile[i] = arcade::TileType::POWERUP;
        } else if (i / HEIGHT == 0 || i / HEIGHT == HEIGHT - 1 || i % WIDTH == 0 || i % WIDTH == WIDTH - 1) {
            map->tile[i] = arcade::TileType::BLOCK;
        } else {
            map->tile[i] = arcade::TileType::EMPTY;
        }
    }
}

void        Snake::whereAmI(struct arcade::WhereAmI *wai)
{
    wai = new arcade::WhereAmI + this->snake.size() * sizeof(arcade::TileType);

    wai->type = arcade::CommandType::WHERE_AM_I;
    wai->lenght = this->snake.size();
    for (size_t i = 0; i < this->snake.size(); i++) {
        wai->position[i].x = this->snake[i]->getPos().x;
        wai->position[i].y = this->snake[i]->getPos().y;
    }
}

void 	Play(void)
{
    Snake               *snake;
    char                cmd;
    arcade::GetMap      *map;
    arcade::WhereAmI    *wai;

    snake = new Snake();
    wai = NULL;
    map = new arcade::GetMap + (WIDTH * HEIGHT) * sizeof(arcade::TileType);
    map->type = arcade::CommandType::GET_MAP;
    map->width = WIDTH;
    map->height = HEIGHT;
    while (std::cin.read(&cmd, 1))
    {
        switch ((arcade::CommandType)cmd) {
            case arcade::CommandType::WHERE_AM_I:
                snake->whereAmI(wai);
                std::cout.write((const char *)wai, sizeof(*wai));
                break;
            case arcade::CommandType::GET_MAP:
                snake->updateMap(map);
                std::cout.write((const char *)map, sizeof(*map));
                break;
            case arcade::CommandType::GO_UP:
                snake->changeDirection(DIR_UP);
                break;
            case arcade::CommandType::GO_DOWN:
                snake->changeDirection(DIR_DOWN);
                break;
            case arcade::CommandType::GO_LEFT:
                snake->changeDirection(DIR_LEFT);
                break;
            case arcade::CommandType::GO_RIGHT:
                snake->changeDirection(DIR_RIGHT);
                break;
            case arcade::CommandType::GO_FORWARD:
                break;
            case arcade::CommandType::PLAY:
                snake->compute(-1);
                break;
            default:
                break;
        }
    }
}
