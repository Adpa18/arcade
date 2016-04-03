#include "Centipede.hpp"

Centipede::Centipede() : AGame("Centipede")
{
    this->obj = new GameComponent(Vector2<double>(ArcadeSystem::winWidth / 2, ArcadeSystem::winHeight / 2), Vector2<double>(1, 1), AComponent::YELLOW, ' ', "", GameComponent::CUBE_LARGE);
}

Centipede::~Centipede()
{}

void 		             Centipede::changeDirection(int key)
{
    Vector2<double>     objPos = this->obj->getPos();

    switch (key) {
        case ArcadeSystem::ArrowLeft:
            objPos.x -= 1;
            if (objPos.x <= 0)
                objPos.x = ArcadeSystem::winWidth - 1;
            break;
        case ArcadeSystem::ArrowRight:
            objPos.x += 1;
            if (objPos.x >= ArcadeSystem::winWidth)
                objPos.x = 0;
            break;
        case ArcadeSystem::ArrowUp:
            objPos.y -= 1;
            break;
        case ArcadeSystem::ArrowDown:
            objPos.y += 1;
            break;
    }
    if (this->check(objPos)) {
        this->obj->setPos(objPos);
    }
}

bool    Centipede::check(Vector2<double> objPos)
{
    if (objPos.x < 1 || objPos.x >= ArcadeSystem::winWidth - 1 || objPos.y < 1 || objPos.y >= ArcadeSystem::winHeight - 1)
        return (false);
    return (true);
}

std::stack<AComponent*>     Centipede::compute(int key)
{
    std::stack<AComponent*> components;

    this->changeDirection(key);
    components.push(this->obj);
    return (components);
}

void				Centipede::restart()
{
    this->obj->setPos(Vector2<double>(ArcadeSystem::winWidth / 2, ArcadeSystem::winHeight / 2));
}

void        Centipede::getMap() const
{
    arcade::GetMap      *map;

    if (!(map = (arcade::GetMap*)malloc(sizeof(arcade::GetMap) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight) * sizeof(arcade::TileType)))) {
        throw std::bad_alloc();
    }
    map->type = arcade::CommandType::GET_MAP;
    map->width = ArcadeSystem::winWidth;
    map->height = ArcadeSystem::winHeight;
    for (size_t i = 0; i < ArcadeSystem::winWidth * ArcadeSystem::winHeight; i++) {
        if (i % ArcadeSystem::winWidth == 0 || i % ArcadeSystem::winWidth == ArcadeSystem::winWidth - 1 || i / ArcadeSystem::winWidth == 0 || i / ArcadeSystem::winWidth == ArcadeSystem::winHeight - 1) {
            map->tile[i] = arcade::TileType::BLOCK;
        } else {
            map->tile[i] = arcade::TileType::EMPTY;
        }
    }
    std::cout.write((const char *)map, sizeof(arcade::GetMap) + (ArcadeSystem::winWidth * ArcadeSystem::winHeight) * sizeof(arcade::TileType));
}

void        Centipede::whereAmI() const
{
    arcade::WhereAmI    *wai;

    if (!(wai = (arcade::WhereAmI*)malloc(sizeof(arcade::WhereAmI) + sizeof(arcade::TileType)))) {
        throw std::bad_alloc();
    }
    wai->type = arcade::CommandType::WHERE_AM_I;
    wai->lenght = 1;
    wai->position[0].x = static_cast<uint16_t>(this->obj->getPos().x);
    wai->position[0].y = static_cast<uint16_t>(this->obj->getPos().y);
    std::cout.write((const char *)wai, sizeof(arcade::WhereAmI) + wai->lenght * sizeof(arcade::Position));
}

void 	Play(void)
{
    Centipede              *obj;
    char                cmd;

    obj = new Centipede();
    while (std::cin.read(&cmd, sizeof(arcade::CommandType)))
    {
        switch ((arcade::CommandType)cmd) {
            case arcade::CommandType::WHERE_AM_I:
                obj->whereAmI();
                break;
            case arcade::CommandType::GET_MAP:
                obj->getMap();
                break;
            case arcade::CommandType::GO_UP:
                obj->changeDirection(ArcadeSystem::ArrowUp);
                break;
            case arcade::CommandType::GO_DOWN:
                obj->changeDirection(ArcadeSystem::ArrowDown);
                break;
            case arcade::CommandType::GO_LEFT:
                obj->changeDirection(ArcadeSystem::ArrowLeft);
                break;
            case arcade::CommandType::GO_RIGHT:
                obj->changeDirection(ArcadeSystem::ArrowRight);
                break;
            case arcade::CommandType::GO_FORWARD:
                break;
            case arcade::CommandType::PLAY:
                obj->compute(-1);
                break;
            default:
                break;
        }
    }
}
