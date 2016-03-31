#include "Ghost.hpp"

Ghost::Ghost (std::map<double, GameComponent*> &mapObjs, Vector2<double> pos,
    AComponent::ComponentColor color, const std::string sprite2D)
    : startPos(pos), status(ALIVE), mapObjs(mapObjs)
{
    this->obj = new GameComponent(pos, Vector2<double>(1, 1), color, ' ', sprite2D, GameComponent::CUBE_LARGE);
    this->init();
}

Ghost::~Ghost()
{

}

void    Ghost::init()
{
    this->obj->setPos(this->startPos);
    std::time(&this->beginTime);
    this->alive();
}

bool    Ghost::check(Vector2<double> pos)
{
    std::map<double, GameComponent*>::iterator  it = mapObjs.find(pos.y * WIDTH + pos.x);

    if (it != mapObjs.end() && it->second->getSpriteText() == "X")
        return (false);
    return (true);
}

void    Ghost::goTo(Vector2<double> pos)
{
    time_t  currentTime;

    std::time(&currentTime);
    if (difftime(currentTime, this->beginTime) > rand() % 5000 + 1000)
        return;
    (void)pos;
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
    this->status = ALIVE;
    // Change Texture
}

void            Ghost::dead()
{
    this->status = DEAD;
    // Change Texture
}

void            Ghost::vulnerable()
{
    this->status = VULNERABLE;
    // Change Texture
}
