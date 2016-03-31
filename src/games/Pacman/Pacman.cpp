#include "Pacman.hpp"

Pacman::Pacman() : AGame("Pacman", Vector2<double>(WIDTH, HEIGHT))
{
    std::string                 sprite2D;
    AComponent::ComponentColor  color;

    this->pacman = new GameComponent(Vector2<double>(25, 18), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "pacman.gif", GameComponent::CUBE_LARGE);
    this->phantom.push_back(new GameComponent(Vector2<double>(25, 13), Vector2<double>(1, 1), AComponent::RED, ' ', "ghost_red.gif", GameComponent::CUBE_LARGE));
    this->phantom.push_back(new GameComponent(Vector2<double>(25, 14), Vector2<double>(1, 1), AComponent::CYAN, ' ', "ghost_cyan.gif", GameComponent::CUBE_LARGE));
    this->phantom.push_back(new GameComponent(Vector2<double>(25, 15), Vector2<double>(1, 1), AComponent::GREEN, ' ', "ghost_orange.gif", GameComponent::CUBE_LARGE));
    this->phantom.push_back(new GameComponent(Vector2<double>(25, 16), Vector2<double>(1, 1), AComponent::MAGENTA, ' ', "ghost_pink.gif", GameComponent::CUBE_LARGE));
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            if (map[y][x] == 'X') {
                sprite2D = "wall.jpg";
                color = AComponent::BLUE;
            } else if (map[y][x] == 'o') {
                sprite2D = "bigBall.png";
                color = AComponent::CYAN;
            } else if (map[y][x] == '.') {
                sprite2D = "smallBall.png";
                color = AComponent::GREEN;
            } else {
                sprite2D = "";
                color = AComponent::BLACK;
            }
            mapObjs[y * WIDTH + x] = new GameComponent(Vector2<double>(x, y), Vector2<double>(1, 1), color, map[y][x], sprite2D, GameComponent::CUBE_LARGE);
        }
    }
    this->restart();
}

Pacman::~Pacman()
{}

bool                        Pacman::check(Vector2<double> pos)
{
    for (std::map<double, GameComponent*>::iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); ++it) {
        if (it->second->getSpriteText() == "X" && it->second->getPos() == pos)
            return (false);
    }
    return (true);
}

void 		             Pacman::changeDirection(int key)
{
    Vector2<double>     pacmanPos = this->pacman->getPos();
    direction           dir;
    static direction    old_dir = NOTHING;

    switch (key) {
        case ArcadeSystem::ArrowLeft:
            dir = DIR_LEFT;
            break;
        case ArcadeSystem::ArrowRight:
            dir = DIR_RIGHT;
            break;
        case ArcadeSystem::ArrowUp:
            dir = DIR_UP;
            break;
        case ArcadeSystem::ArrowDown:
            dir = DIR_DOWN;
            break;
        default:
            dir = old_dir;
            break;
    }
    switch (dir) {
        case DIR_LEFT:
            pacmanPos.x -= 1;
            if (pacmanPos.x <= 0)
                pacmanPos.x = WIDTH - 1;
            break;
        case DIR_RIGHT:
            pacmanPos.x += 1;
            if (pacmanPos.x >= WIDTH)
                pacmanPos.x = 0;
            break;
        case DIR_UP:
            pacmanPos.y -= 1;
            break;
        case DIR_DOWN:
            pacmanPos.y += 1;
            break;
        default:
            return;
    }
    if (dir != NOTHING && this->dir != dir && this->check(pacmanPos)) {
        if (dir == old_dir)
            old_dir = NOTHING;
        this->dir = dir;
    } else if (dir != NOTHING) {
        old_dir = dir;
    }
}

void                Pacman::move()
{
    Vector2<double>         pacmanPos = this->pacman->getPos();

    switch (this->dir) {
        case DIR_LEFT:
            pacmanPos.x -= 1;
            if (pacmanPos.x <= 0)
                pacmanPos.x = WIDTH - 1;
            break;
        case DIR_RIGHT:
            pacmanPos.x += 1;
            if (pacmanPos.x >= WIDTH)
                pacmanPos.x = 0;
            break;
        case DIR_UP:
            pacmanPos.y -= 1;
            break;
        case DIR_DOWN:
            pacmanPos.y += 1;
            break;
        default:
            return;
    }
    if (this->check(pacmanPos)) {
        this->pacman->setPos(pacmanPos);
    }
}

void                Pacman::eat()
{
    Vector2<double>         pacmanPos = this->pacman->getPos();
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pacmanPos.y * WIDTH + pacmanPos.x);

    if (it != mapObjs.end())
        mapObjs.erase(it);
}

std::stack<AComponent*>     Pacman::compute(int key)
{
    std::stack<AComponent*> components;

    this->changeDirection(key);
    this->move();
    this->eat();
    components.push(this->pacman);
    components.push(this->phantom[0]);
    components.push(this->phantom[1]);
    components.push(this->phantom[2]);
    components.push(this->phantom[3]);
    // for (std::map<double, GameComponent*>::iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); ++it) {
    //     components.push(it->second);
    // }
    return (components);
}

std::stack<AComponent*>     Pacman::getInfos()
{
    std::stack<AComponent*> components;

    for (std::map<double, GameComponent*>::iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); ++it) {
        components.push(it->second);
    }
    components.push(this->pacman);
    components.push(this->phantom[0]);
    components.push(this->phantom[1]);
    components.push(this->phantom[2]);
    components.push(this->phantom[3]);
    return (components);
}

void				Pacman::restart()
{
    this->pacman->setPos(Vector2<double>(25, 18));
    this->phantom[0]->setPos(Vector2<double>(25, 13));
    this->phantom[1]->setPos(Vector2<double>(25, 14));
    this->phantom[2]->setPos(Vector2<double>(25, 15));
    this->phantom[3]->setPos(Vector2<double>(25, 16));
    this->dir = DIR_LEFT;
}
