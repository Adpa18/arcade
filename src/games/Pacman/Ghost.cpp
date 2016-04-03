#include "Ghost.hpp"

Ghost::Ghost (std::map<double, GameComponent*> &mapObjs, Vector2<double> pos,
    AComponent::ComponentColor color, const std::string sprite2D)
    : startPos(pos), status(ALIVE), mapObjs(mapObjs), sprite2D(sprite2D)
{
    this->obj = new GameComponent(pos, Vector2<double>(1, 1), color, ' ', sprite2D, GameComponent::CUBE_LARGE);
    this->init();
    this->first_color = color;
    this->slow = true;
}

Ghost::~Ghost()
{

}

void    Ghost::init()
{
    this->dir = NOTHING;
    this->force_dir = false;
    this->obj->setPos(this->startPos);
    this->alive();
}

bool    Ghost::check(Vector2<double> pos)
{
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pos.y * ArcadeSystem::winWidth + pos.x);

    if (it != mapObjs.end() && (it->second->getSpriteText() == "X" || (this->getState() != Ghost::DEAD && it->second->getPos().x == 25 && it->second->getPos().y == 12)))
        return (false);
    return (true);
}

bool	Ghost::tryMove()
{
    Vector2<double>         ghostPos = this->obj->getPos();

    switch (this->dir) {
        case DIR_LEFT:
            ghostPos.x -= STEP;
            if (ghostPos.x <= 0)
                ghostPos.x = WIDTH - 1;
            break;
        case DIR_RIGHT:
            ghostPos.x += STEP;
            if (ghostPos.x >= WIDTH)
                ghostPos.x = 0;
            break;
        case DIR_UP:
            ghostPos.y -= STEP;
            break;
        case DIR_DOWN:
            ghostPos.y += STEP;
            break;
        default:
            return (false);
    }
    if (this->check(ghostPos) || this->isInside()) {
        this->obj->setPos(ghostPos);
        return (true);
    }
    else {
        this->force_dir = false;
        return (false);
    }
}

bool	Ghost::isInside()
{
    Vector2<double>		ghostPos = this->obj->getPos();

    if (ghostPos.x > 22 && ghostPos.x < 28 && ghostPos.y > 11 && ghostPos.y < 17)
        return (true);
    return (false);
}

bool	Ghost::otherWay()
{
    if (this->dir == DIR_LEFT || this->dir == DIR_RIGHT) {
        if (check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y + 1)) || check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y - 1)))
            return (true);
    } else if (check(Vector2<double>(this->obj->getPos().x + 1, this->obj->getPos().y)) || check(Vector2<double>(this->obj->getPos().x - 1, this->obj->getPos().y)))
            return (true);
    return (false);
}

void	Ghost::goToInv(Vector2<double> pos)
{
    if (pos.y - this->obj->getPos().y < 0 && ((check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y - 1)) && this->dir != DIR_DOWN))) {
        this->dir = DIR_UP;
        this->force_dir = false;
        tryMove();
    } else if (pos.y - this->obj->getPos().y < 0 && ((check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y + 1)) && this->dir != DIR_UP))) {
        this->dir = DIR_DOWN;
        this->force_dir = false;
        tryMove();
    } else if (pos.x - this->obj->getPos().x > 0 && ((check(Vector2<double>(this->obj->getPos().x + 1, this->obj->getPos().y)) && this->dir != DIR_LEFT))) {
        this->dir = DIR_RIGHT;
        this->force_dir = false;
        tryMove();
    } else if (pos.x - this->obj->getPos().x < 0 && ((check(Vector2<double>(this->obj->getPos().x - 1, this->obj->getPos().y)) && this->dir != DIR_RIGHT))) {
        this->dir = DIR_LEFT;
        this->force_dir = false;
        tryMove();
    } else {
        while (tryMove() != true) {
            switch (rand() % 4) {
                case 0:
                    this->dir = DIR_LEFT;
                    break;
                case 1:
                    this->dir = DIR_RIGHT;
                    break;
                case 2:
                    this->dir = DIR_UP;
                    break;
                case 3:
                    this->dir = DIR_DOWN;
                    break;
            }
        }
        this->force_dir = true;
    }
}

void			Ghost::inverseDir()
{
    switch (this->dir) {
        case DIR_DOWN:
            this->dir = DIR_UP;
            break;
        case DIR_UP:
            this->dir = DIR_DOWN;
            break;
        case DIR_LEFT:
            this->dir = DIR_RIGHT;
            break;
        case DIR_RIGHT:
            this->dir = DIR_LEFT;
            break;
        default:
            this->dir = NOTHING;
            break;
    }
}
//
// void			Ghost::goToRand(Vector2<double> pos)
// {
//     direction	oldDir;
//
//     if (this->status == DEAD) {
//         pos = this->startPos;
//     }
//     this->slow = !this->slow;
//     if (this->getState() == VULNERABLE && this->slow != true)
//         return;
//     if (this->isInside() == true) {
//         dir = DIR_UP;
//         if (tryMove() == false) {
//             dir = pos.x - this->obj->getPos().x < 0 ? DIR_RIGHT : DIR_LEFT;
//             tryMove();
//             return;
//         }
//     }
//     if (!otherWay()) {
//         if (tryMove() == true)
//             return;
//     }
//     inverseDir();
//     oldDir = this->dir;
//     switch (rand() % 4) {
//         case 0:
//             this->dir = DIR_LEFT;
//             break;
//         case 1:
//             this->dir = DIR_RIGHT;
//             break;
//         case 2:
//             this->dir = DIR_UP;
//             break;
//         case 3:
//             this->dir = DIR_DOWN;
//             break;
//     }
//     while (this->dir == oldDir || tryMove() != true) {
//         switch (rand() % 4) {
//             case 0:
//             this->dir = DIR_LEFT;
//             break;
//             case 1:
//             this->dir = DIR_RIGHT;
//             break;
//             case 2:
//             this->dir = DIR_UP;
//             break;
//             case 3:
//             this->dir = DIR_DOWN;
//             break;
//         }
//     }
// }

void	Ghost::goTo(Vector2<double> pos)
{
    if (this->status == DEAD) {
        pos = this->startPos;
    }
    this->slow = !this->slow;
    if (this->getState() == Ghost::VULNERABLE && this->slow != true) {
        return;
    }
    if (this->getState() != Ghost::DEAD && this->isInside() == true) {
        dir = DIR_UP;
        tryMove();
        return;
    } else if (this->getState() == Ghost::DEAD && this->isInside() == true) {
        this->alive();
    }
    if (this->getState() == Ghost::DEAD) {
        if (this->obj->getPos().x == 25 && this->obj->getPos().y == 11) {
            this->dir = DIR_DOWN;
            tryMove();
        }
    }
    if (this->dir != NOTHING && this->force_dir != true && tryMove() == true) {
        this->force_dir = false;
        return;
    }
    if (otherWay()) {
        goToInv(pos);
    }
    if (pos.x - this->obj->getPos().x > 0 && ((check(Vector2<double>(this->obj->getPos().x + 1, this->obj->getPos().y)) && this->dir != DIR_LEFT))) {
        this->dir = DIR_RIGHT;
        this->force_dir = false;
        tryMove();
    } else if (pos.x - this->obj->getPos().x < 0 && ((check(Vector2<double>(this->obj->getPos().x - 1, this->obj->getPos().y)) && this->dir != DIR_RIGHT))) {
        this->dir = DIR_LEFT;
        this->force_dir = false;
        tryMove();
    } else if (pos.y - this->obj->getPos().y < 0 && ((check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y - 1)) && this->dir != DIR_DOWN))) {
        this->dir = DIR_UP;
        this->force_dir = false;
        tryMove();
    } else if (pos.y - this->obj->getPos().y < 0 && ((check(Vector2<double>(this->obj->getPos().x, this->obj->getPos().y + 1)) && this->dir != DIR_UP))) {
        this->dir = DIR_DOWN;
        this->force_dir = false;
        tryMove();
    } else {
        while (tryMove() != true) {
            switch (rand() % 4) {
                case 0:
                    this->dir = DIR_LEFT;
                    break;
                case 1:
                    this->dir = DIR_RIGHT;
                    break;
                case 2:
                    this->dir = DIR_UP;
                    break;
                case 3:
                    this->dir = DIR_DOWN;
                    break;
            }
        }
        this->force_dir = true;
    }
}

GameComponent   *Ghost::getObj() const
{
    return (this->obj);
}

Ghost::state    Ghost::getState() const
{
    return (this->status);
}

Vector2<double> Ghost::getStartPos() const
{
    return (this->startPos);
}

void            Ghost::alive()
{
    this->status = Ghost::ALIVE;
    this->obj->setSprite2D(this->sprite2D);
    this->obj->setColor(this->first_color);
}

void            Ghost::dead()
{
    this->status = Ghost::DEAD;
    this->obj->setColor(AComponent::WHITE);
    this->obj->setSprite2D("eyes2.png");
}

void            Ghost::vulnerable()
{
    this->status = Ghost::VULNERABLE;
    this->obj->setColor(AComponent::BLUE);
    this->obj->setSprite2D("ghost_dead.gif");
}
