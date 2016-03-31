#include "Snake.hpp"

Snake::Snake () : AGame("Snake", Vector2<double>(WIDTH, HEIGHT))
{
    this->target = new GameComponent(RANDOM_POS, Vector2<double>(1, 1), AComponent::RED, ' ', "snakeApple.png", GameComponent::CUBE_LARGE);
    this->background = new BackgroundComponent(Vector2<double>(0, 0), Vector2<double>(WIDTH, HEIGHT), AComponent::BLACK, "");
    for (size_t i = 0; i < WIDTH; i += 1) {
        this->walls.push_back(new GameComponent(Vector2<double>(i, 0), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "wall1.png", GameComponent::CUBE_LARGE));
        this->walls.push_back(new GameComponent(Vector2<double>(i, HEIGHT - 1), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "wall1.png", GameComponent::CUBE_LARGE));
    }
    for (size_t i = 0; i < HEIGHT; i += 1) {
        this->walls.push_back(new GameComponent(Vector2<double>(0, i), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "wall1.png", GameComponent::CUBE_LARGE));
        this->walls.push_back(new GameComponent(Vector2<double>(WIDTH - 1, i), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "wall1.png", GameComponent::CUBE_LARGE));
    }
    this->restart();
}

Snake::~Snake ()
{}

void    Snake::restart()
{
    static const char * const backgroundSprites[] = {
        "snakeBackground.jpg",
        "snakeBackground1.jpg",
        "snakeBackground2.jpg"
    };
    this->dir = DIR_UP;
    this->background->setSprite2D(backgroundSprites[rand() % 3]);
    this->snake.erase(this->snake.begin(), this->snake.end());
    for (size_t i = 0; i < SIZE; i++) {
      this->snake.push_back(new GameComponent(Vector2<double>(WIDTH / 2 - i, HEIGHT / 2), Vector2<double>(1, 1), AComponent::RED, ' ', "", GameComponent::CUBE_LARGE));
    }
    this->target->setPos(RANDOM_POS);
}

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
        if (pos0.x == pos1.x - 1) {
            img += "L";
        } else if (pos0.x == pos1.x + 1) {
            img += "R";
        } else if (pos0.y == pos1.y - 1) {
            img += "T";
        } else if (pos0.y == pos1.y + 1) {
            img += "B";
        }
    } else {
        Vector2<double> pos0 = this->snake[pos]->getPos();
        Vector2<double> pos1 = this->snake[pos - 1]->getPos();
        Vector2<double> pos2 = this->snake[pos + 1]->getPos();
        if ((pos0.x == pos1.x + 1 && pos0.x == pos2.x - 1)
            || (pos0.x == pos1.x - 1 && pos0.x == pos2.x + 1)) {
            img += "H";
        } else if ((pos0.y == pos1.y + 1 && pos0.y == pos2.y - 1)
            || (pos0.y == pos1.y - 1 && pos0.y == pos2.y + 1)) {
                img += "V";
        } else {
            if (pos0.x == pos1.x + 1 || pos0.x == pos2.x + 1) {
                img += "Left";
            } else {
                img += "Right";
            }
            if (pos0.y == pos1.y + 1 || pos0.y == pos2.y + 1) {
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
            snakePos.x -= 1;
            break;
        case DIR_RIGHT:
            snakePos.x += 1;
            break;
        case DIR_UP:
            snakePos.y -= 1;
            break;
        case DIR_DOWN:
            snakePos.y += 1;
            break;
    }
    if (check(snakePos)) {
        this->snake.insert(this->snake.begin(), new GameComponent(snakePos, Vector2<double>(1, 1), AComponent::GREEN, ' ', "", GameComponent::CUBE_LARGE));
        if (this->snake.front()->getPos() == this->target->getPos()) {
            this->target->setPos(RANDOM_POS);
            components.push(this->target);
        } else {
            this->snake.pop_back();
        }
    } else {
        this->restart();
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

void        Snake::getMap()
{
    arcade::GetMap      *map;

    map = new arcade::GetMap + (WIDTH * HEIGHT) * sizeof(arcade::TileType);
    map->type = arcade::CommandType::GET_MAP;
    map->width = WIDTH;
    map->height = HEIGHT;
    for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
        if (i % WIDTH == 0 || i % WIDTH == WIDTH - 1 || i / WIDTH == 0 || i / WIDTH == HEIGHT - 1) {
            map->tile[i] = arcade::TileType::BLOCK;
        } else if (this->target->getPos().y * WIDTH + this->target->getPos().x == i) {
            map->tile[i] = arcade::TileType::POWERUP;
        } else {
            map->tile[i] = arcade::TileType::EMPTY;
        }
    }
    std::cout.write((const char *)map, sizeof(arcade::GetMap) + (WIDTH * HEIGHT) * sizeof(arcade::TileType));
}

void        Snake::whereAmI()
{
    arcade::WhereAmI    *wai;

    wai = new arcade::WhereAmI + this->snake.size() * sizeof(arcade::Position);

    wai->type = arcade::CommandType::WHERE_AM_I;
    wai->lenght = static_cast<uint16_t>(this->snake.size());
    for (uint16_t i = 0; i < wai->lenght; i++) {
        wai->position[i].x = static_cast<uint16_t>(this->snake[i]->getPos().x);
        wai->position[i].y = static_cast<uint16_t>(this->snake[i]->getPos().y);
    }
    std::cout.write((const char *)wai, sizeof(arcade::WhereAmI) + wai->lenght * sizeof(arcade::Position));
}

void 	Play(void)
{
    Snake               *snake;
    char                cmd;

    snake = new Snake();
    while (std::cin.read(&cmd, 1))
    {
        switch ((arcade::CommandType)cmd) {
            case arcade::CommandType::WHERE_AM_I:
                snake->whereAmI();
                break;
            case arcade::CommandType::GET_MAP:
                snake->getMap();
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
