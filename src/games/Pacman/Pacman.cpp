#include "Pacman.hpp"

Pacman::Pacman() : AGame("Pacman")
{
    this->pacman = new GameComponent(Vector2<double>(26, 18), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "pacman.gif", GameComponent::CUBE_LARGE);
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 13), AComponent::RED, "ghost_red.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 14), AComponent::CYAN, "ghost_cyan.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 15), AComponent::GREEN, "ghost_orange.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 16), AComponent::MAGENTA, "ghost_pink.gif"));
    this->restart();
}

Pacman::~Pacman()
{}

bool                        Pacman::check(Vector2<double> pos)
{
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pos.y * ArcadeSystem::winWidth + pos.x);

    if (it != mapObjs.end() && (it->second->getSpriteText() == "X" || (it->second->getPos().x == 25 && it->second->getPos().y == 12)))
        return (false);
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
            pacmanPos.x -= STEP;
            if (pacmanPos.x <= 0)
                pacmanPos.x = ArcadeSystem::winWidth - 1;
            break;
        case DIR_RIGHT:
            pacmanPos.x += STEP;
            if (pacmanPos.x >= ArcadeSystem::winWidth)
                pacmanPos.x = 0;
            break;
        case DIR_UP:
            pacmanPos.y -= STEP;
            break;
        case DIR_DOWN:
            pacmanPos.y += STEP;
            break;
        default:
            return;
    }
    if (dir != NOTHING && this->dir != dir && this->check(pacmanPos)) {
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
            pacmanPos.x -= STEP;
            if (pacmanPos.x <= 0)
                pacmanPos.x = ArcadeSystem::winWidth - 1;
            break;
        case DIR_RIGHT:
            pacmanPos.x += STEP;
            if (pacmanPos.x >= ArcadeSystem::winWidth)
                pacmanPos.x = 0;
            break;
        case DIR_UP:
            pacmanPos.y -= STEP;
            break;
        case DIR_DOWN:
            pacmanPos.y += STEP;
            break;
        default:
            return;
    }
    if (this->check(pacmanPos)) {
        this->pacman->setPos(pacmanPos);
    }
    this->ghosts[0]->goTo(this->pacman->getPos());
    this->ghosts[1]->goTo(this->pacman->getPos());
    this->ghosts[2]->goToRand(this->pacman->getPos());
    this->ghosts[3]->goToRand(this->pacman->getPos());
}

void                Pacman::eat()
{
    Vector2<double>         pacmanPos = this->pacman->getPos();
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pacmanPos.y * ArcadeSystem::winWidth + pacmanPos.x);

    if (it != mapObjs.end())
        mapObjs.erase(it);
}

bool						Pacman::is_empty()
{
    for (std::map<double, GameComponent*>::iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); it++) {
        if (it->second->getSpriteText() == "o" || it->second->getSpriteText() == ".")
          return (false);
    }
    return (true);
}

std::stack<AComponent*>     Pacman::compute(int key)
{
    std::stack<AComponent*> components;

    if (this->play_state == ON_GAME && (key == ArcadeSystem::Enter || key == 10))
        this->play_state = ON_PAUSE;
    else if (this->play_state == ON_GAME) {
        if (this->is_empty() == true)
            this->restart();
        this->changeDirection(key);
        this->move();
        this->eat();
    }
    else if (this->play_state == ON_START && (key == ArcadeSystem::Enter || key == 10)) {
        this->play_state = ON_GAME;
        this->ghosts[0]->init();
        this->ghosts[1]->init();
        this->ghosts[2]->init();
        this->ghosts[3]->init();
    }
    else if (this->play_state == ON_PAUSE && (key == ArcadeSystem::Enter || key == 10)) {
        this->play_state = ON_GAME;
    }
    components.push(this->pacman);
    components.push(this->ghosts[0]->getObj());
    components.push(this->ghosts[1]->getObj());
    components.push(this->ghosts[2]->getObj());
    components.push(this->ghosts[3]->getObj());
    for (std::map<double, GameComponent*>::iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); ++it) {
        components.push(it->second);
    }
    return (components);
}

std::stack<AComponent*>     Pacman::getInfos() const
{
    std::stack<AComponent*> components;

    components.push(this->pacman);
    components.push(this->ghosts[0]->getObj());
    components.push(this->ghosts[1]->getObj());
    components.push(this->ghosts[2]->getObj());
    components.push(this->ghosts[3]->getObj());
    for (std::map<double, GameComponent*>::const_iterator it = this->mapObjs.begin(); it != this->mapObjs.end(); ++it) {
        components.push(it->second);
    }
    return (components);
}

void				Pacman::restart()
{
    std::string                 sprite2D;
    AComponent::ComponentColor  color;

    this->pacman->setPos(Vector2<double>(25, 18));
    this->ghosts[0]->init();
    this->ghosts[1]->init();
    this->ghosts[2]->init();
    this->ghosts[3]->init();
    this->dir = DIR_LEFT;
    this->play_state = ON_START;
    for (size_t y = 0; y < ArcadeSystem::winHeight; y++) {
        for (size_t x = 0; x < ArcadeSystem::winWidth; x++) {
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
            mapObjs[y * ArcadeSystem::winWidth + x] = new GameComponent(Vector2<double>(x, y), Vector2<double>(1, 1), color, map[y][x], sprite2D, GameComponent::CUBE_LARGE);
        }
    }
}
