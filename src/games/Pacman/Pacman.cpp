#include "Pacman.hpp"

Pacman::Pacman() : AGame("Pacman")
{
    this->pacman = new GameComponent(Vector2<double>(25, 18), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "pacman.gif", GameComponent::CUBE_LARGE);
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 13), AComponent::RED, "ghost_red.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 14), AComponent::CYAN, "ghost_cyan.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 15), AComponent::GREEN, "ghost_orange.gif"));
    this->ghosts.push_back(new Ghost(mapObjs, Vector2<double>(25, 16), AComponent::MAGENTA, "ghost_pink.gif"));
    this->scoreText = new UIComponent(Vector2<double>(ArcadeSystem::winWidth / 2, 0), AComponent::WHITE, Vector2<double>(0, 0), "Score : 0");
    this->nbLivesText = new UIComponent(Vector2<double>(2, 0), AComponent::WHITE, Vector2<double>(0, 0), "Lives : 3");
    this->highScore = NULL;
    this->restart();
}

Pacman::~Pacman()
{}

void				Pacman::restart()
{
    this->nb_life = 3;
    this->scoreText->setText("Score : 0");
    this->nbLivesText->setText("Lives : 3");
    this->score = 0;
    this->started = false;
    std::time(&this->startTime);
    this->init();
}

void				Pacman::restart_with_life()
{
    this->pacman->setPos(Vector2<double>(25, 18));
    this->ghosts[0]->init();
    this->ghosts[1]->init();
    this->ghosts[2]->init();
    this->ghosts[3]->init();
    this->dir = DIR_LEFT;
    this->play_state = ALIVE;
    this->eat_state = NORMAL;
    --this->nb_life;
    this->nbLivesText->setText("Lives : " + std::to_string(this->nb_life));
}

void    Pacman::init()
{
    std::string                 sprite2D;
    AComponent::ComponentColor  color;

    this->pacman->setPos(Vector2<double>(25, 18));
    this->ghosts[0]->init();
    this->ghosts[1]->init();
    this->ghosts[2]->init();
    this->ghosts[3]->init();
    this->dir = DIR_LEFT;
    this->play_state = ALIVE;
    this->eat_state = NORMAL;
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
                continue;
            }
            mapObjs[y * ArcadeSystem::winWidth + x] = new GameComponent(Vector2<double>(x, y), Vector2<double>(1, 1), color, map[y][x], sprite2D, GameComponent::CUBE_LARGE);
        }
    }
}

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

void                Pacman::checkEvent()
{
    if (this->pacman->getPos() == this->ghosts[0]->getObj()->getPos()) {
        if (this->eat_state == INVINCIBLE && this->ghosts[0]->getState() == Ghost::VULNERABLE) {
            this->ghosts[0]->dead();
            this->score += 200;
        } else if (this->eat_state != INVINCIBLE && this->ghosts[0]->getState() == Ghost::ALIVE) {
            this->play_state = DEAD;
            return;
        }
    }
    if (this->pacman->getPos() == this->ghosts[1]->getObj()->getPos()) {
        if (this->eat_state == INVINCIBLE && this->ghosts[1]->getState() == Ghost::VULNERABLE) {
            this->ghosts[1]->dead();
            this->score += 200;
        } else if (this->eat_state != INVINCIBLE && this->ghosts[1]->getState() == Ghost::ALIVE) {
            this->play_state = DEAD;
            return;
        }
    }
    if (this->pacman->getPos() == this->ghosts[2]->getObj()->getPos()) {
        if (this->eat_state == INVINCIBLE && this->ghosts[2]->getState() == Ghost::VULNERABLE) {
            this->ghosts[2]->dead();
            this->score += 200;
        } else if (this->eat_state != INVINCIBLE && this->ghosts[2]->getState() == Ghost::ALIVE) {
            this->play_state = DEAD;
            return;
        }
    }
    if (this->pacman->getPos() == this->ghosts[2]->getObj()->getPos()) {
        if (this->eat_state == INVINCIBLE && this->ghosts[2]->getState() == Ghost::VULNERABLE) {
            this->ghosts[2]->dead();
            this->score += 200;
        } else if (this->eat_state != INVINCIBLE && this->ghosts[3]->getState() == Ghost::ALIVE) {
            this->play_state = DEAD;
            return;
        }
    }
}

void                Pacman::move()
{
    time_t          currentTime;
    Vector2<double> pacmanPos = this->pacman->getPos();

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
    if (!this->started) {
        std::time(&currentTime);
        if (difftime(currentTime, this->startTime) >= 10) {
            this->started = true;
        }
        return;
    }
    this->checkEvent();
    this->ghosts[0]->goTo(this->pacman->getPos());
    this->ghosts[1]->goTo(this->pacman->getPos());
    this->ghosts[2]->goTo(this->pacman->getPos());
    this->ghosts[3]->goTo(this->pacman->getPos());
    this->checkEvent();
}

void                Pacman::eat()
{
    Vector2<double>         pacmanPos = this->pacman->getPos();
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pacmanPos.y * ArcadeSystem::winWidth + pacmanPos.x);

    if (it != mapObjs.end()) {
        if (it->second->getSpriteText() == "o") {
            this->eat_state = INVINCIBLE;
            this->score += 90;
            if (this->ghosts[0]->getState() != Ghost::DEAD) {
                this->ghosts[0]->vulnerable();
            }
            if (this->ghosts[1]->getState() != Ghost::DEAD) {
                this->ghosts[1]->vulnerable();
            }
            if (this->ghosts[2]->getState() != Ghost::DEAD) {
                this->ghosts[2]->vulnerable();
            }
            if (this->ghosts[3]->getState() != Ghost::DEAD) {
                this->ghosts[3]->vulnerable();
            }
            std::time(&this->beginTime);
        }
        mapObjs.erase(it);
        this->score += 10;
    }
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
    time_t					currentTime;

    if (this->play_state == ALIVE) {
        if (this->is_empty() == true) {
            this->init();
        }
        this->changeDirection(key);
        this->move();
        this->eat();
    }
    if (this->eat_state == INVINCIBLE) {
        std::time(&currentTime);
        if (difftime(currentTime, this->beginTime) > 10) {
            this->eat_state = NORMAL;
            for (short i = 0; i < 4; i++) {
                if (this->ghosts[i]->getState() != Ghost::DEAD) {
                    this->ghosts[i]->alive();
                }
            }
        }
    }
    if (this->play_state == DEAD && this->nb_life > 1) {
        this->restart_with_life();
    } else if (this->play_state == DEAD) {
        if (!this->highScore) {
            highScore = new HighScoreComponent("pacman", this->score);
        }
        highScore->UpdatePseudo(key);
        if (key == ArcadeSystem::Enter && highScore->submit()) {
            this->state = ALIVE;
            delete highScore;
            highScore = NULL;
            this->restart();
        } else {
            components.push(highScore);
        }
    }
    this->scoreText->setText("Score : " + std::to_string(this->score));
    components.push(this->scoreText);
    components.push(this->nbLivesText);
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

void        Pacman::getMap() const
{
    arcade::GetMap      *map;

    if (!(map = (arcade::GetMap*)malloc(sizeof(arcade::GetMap) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight) * sizeof(arcade::TileType)))) {
        throw std::bad_alloc();
    }
    map->type = arcade::CommandType::GET_MAP;
    map->width = ArcadeSystem::winWidth;
    map->height = ArcadeSystem::winHeight;
    for (size_t i = 0; i < ArcadeSystem::winWidth * ArcadeSystem::winHeight; i++) {
        if (this->map[i / ArcadeSystem::winWidth][i % ArcadeSystem::winWidth] == 'X') {
            map->tile[i] = arcade::TileType::BLOCK;
        }else if (this->map[i / ArcadeSystem::winWidth][i % ArcadeSystem::winWidth] == 'o') {
            map->tile[i] = arcade::TileType::POWERUP;
        } else {
            map->tile[i] = arcade::TileType::EMPTY;
        }
    }
    std::cout.write((const char *)map, sizeof(arcade::GetMap) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight) * sizeof(arcade::TileType));
}

void        Pacman::whereAmI() const
{
    arcade::WhereAmI    *wai;

    if (!(wai = (arcade::WhereAmI*)malloc(sizeof(arcade::WhereAmI) + sizeof(arcade::TileType)))) {
        throw std::bad_alloc();
    }
    wai->type = arcade::CommandType::WHERE_AM_I;
    wai->lenght = 1;
    wai->position[0].x = static_cast<uint16_t>(this->pacman->getPos().x);
    wai->position[0].y = static_cast<uint16_t>(this->pacman->getPos().y);
    std::cout.write((const char *)wai, sizeof(arcade::WhereAmI) + wai->lenght * sizeof(arcade::Position));
}

void 	Play(void)
{
    Pacman              *pacman;
    char                cmd;

    pacman = new Pacman();
    while (std::cin.read(&cmd, sizeof(arcade::CommandType)))
    {
        switch ((arcade::CommandType)cmd) {
            case arcade::CommandType::WHERE_AM_I:
                pacman->whereAmI();
                break;
            case arcade::CommandType::GET_MAP:
                pacman->getMap();
                break;
            case arcade::CommandType::GO_UP:
                pacman->changeDirection(ArcadeSystem::ArrowUp);
                break;
            case arcade::CommandType::GO_DOWN:
                pacman->changeDirection(ArcadeSystem::ArrowDown);
                break;
            case arcade::CommandType::GO_LEFT:
                pacman->changeDirection(ArcadeSystem::ArrowLeft);
                break;
            case arcade::CommandType::GO_RIGHT:
                pacman->changeDirection(ArcadeSystem::ArrowRight);
                break;
            case arcade::CommandType::GO_FORWARD:
                break;
            case arcade::CommandType::PLAY:
                pacman->compute(-1);
                break;
            default:
                break;
        }
    }
}
