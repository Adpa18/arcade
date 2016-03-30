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
            mapObjs.push_back(new GameComponent(Vector2<double>(x, y), Vector2<double>(1, 1), color, map[y][x], sprite2D, GameComponent::CUBE_LARGE));
        }
    }
    this->restart();
}

Pacman::~Pacman()
{}

bool                        Pacman::check(Vector2<double> pos)
{
    for (size_t i = 0; i < this->mapObjs.size(); i++) {
        if (this->mapObjs[i]->getPos() == pos)
            return (false);
    }
    return (true);
}

std::stack<AComponent*>     Pacman::compute(int key)
{
    std::stack<AComponent*> components;
    Vector2<double>         pacmanPos = this->pacman->getPos();

    switch (key) {
        case ArcadeSystem::ArrowLeft:
            pacmanPos.x -= 1;
            if (pacmanPos.x <= 0)
                pacmanPos.x = WIDTH - 1;
            break;
        case ArcadeSystem::ArrowRight:
            pacmanPos.x += 1;
            if (pacmanPos.x >= WIDTH)
                pacmanPos.x = 0;
            break;
        case ArcadeSystem::ArrowUp:
            pacmanPos.y -= 1;
            break;
        case ArcadeSystem::ArrowDown:
            pacmanPos.y += 1;
            break;
    }
    // if (this->check(pacmanPos))
    // {
        std::cout << this->pacman->getPos() << std::endl;
        this->pacman->setPos(pacmanPos);
        std::cout << this->pacman->getPos() << std::endl;
    // }
    components.push(this->pacman);
    components.push(this->phantom[0]);
    components.push(this->phantom[1]);
    components.push(this->phantom[2]);
    components.push(this->phantom[3]);
    for (size_t i = 0; i < this->mapObjs.size(); i++) {
        components.push(this->mapObjs[i]);
    }
    return (components);
}

void				Pacman::restart()
{
    this->pacman->setPos(Vector2<double>(25, 18));
    this->phantom[0]->setPos(Vector2<double>(25, 13));
    this->phantom[1]->setPos(Vector2<double>(25, 14));
    this->phantom[2]->setPos(Vector2<double>(25, 15));
    this->phantom[3]->setPos(Vector2<double>(25, 16));
}

std::stack<AComponent*>     Pacman::getInfos()
{
    std::stack<AComponent*> components;

    for (size_t i = 0; i < this->mapObjs.size(); i++) {
        components.push(this->mapObjs[i]);
    }
    components.push(this->pacman);
    components.push(this->phantom[0]);
    components.push(this->phantom[1]);
    components.push(this->phantom[2]);
    components.push(this->phantom[3]);
    return (components);
}

//
// bool				Pacman::limit(Vector2<double> tmp)
// {
//   if (tmp.x < 0 || tmp.x >= WIDTH || tmp.y < 0 || tmp.y >= HEIGHT)
//     return (true);
//   else
//     return (false);
// }
//
// bool				Pacman::tryDown(Vector2<double> pos)
// {
//   if (pos.y + STEP >= HEIGHT)
//     return (false);
//   else
//     return (true);
// }
//
// bool				Pacman::tryUp(Vector2<double> pos)
// {
//   if (pos.y - STEP <= 0)
//     return (false);
//   else
//     return (true);
// }
//
// bool				Pacman::tryRight(Vector2<double> pos)
// {
//   if (pos.x + STEP >= WIDTH)
//     return (false);
//   else
//     return (true);
// }
//
// bool				Pacman::tryLeft(Vector2<double> pos)
// {
//   if (pos.x - STEP <= 0)
//     return (false);
//   else
//     return (true);
// }
//
// void				Pacman::newDir(GameComponent *phant)
// {
//   direction			save;
//   Vector2<double>			pos = phant->getPos();
//   int				aleat;
//
//   save = dir[phant];
//   aleat = rand() % 2;
//   if (save == DIR_LEFT || save == DIR_RIGHT) {
//     if (aleat == 0) {
//       if (tryDown(pos) == true)
//         dir[phant] = DIR_DOWN;
//       else if (tryUp(pos) == true)
//         dir[phant] = DIR_UP;
//       else if (tryLeft(pos) == true)
//         dir[phant] = DIR_LEFT;
//       else if (tryRight(pos) == true)
//         dir[phant] = DIR_RIGHT;
//       else
//         dir[phant] = WAIT;
//     }
//     else {
//       if (tryUp(pos) == true)
//         dir[phant] = DIR_UP;
//       else if (tryDown(pos) == true)
//         dir[phant] = DIR_DOWN;
//       else if (tryRight(pos) == true)
//         dir[phant] = DIR_RIGHT;
//       else if (tryLeft(pos) == true)
//         dir[phant] = DIR_LEFT;
//       else
//         dir[phant] = WAIT;
//     }
//   }
//   else if (save == DIR_DOWN || save == DIR_UP) {
//     if (aleat == 0) {
//       if (tryLeft(pos) == true)
//         dir[phant] = DIR_LEFT;
//       else if (tryRight(pos) == true)
//         dir[phant] = DIR_RIGHT;
//       else if (tryDown(pos) == true)
//         dir[phant] = DIR_DOWN;
//       else if (tryUp(pos) == true)
//         dir[phant] = DIR_UP;
//       else
//         dir[phant] = WAIT;
//     }
//     else {
//       if (tryRight(pos) == true)
//         dir[phant] = DIR_RIGHT;
//       else if (tryLeft(pos) == true)
//         dir[phant] = DIR_LEFT;
//       else if (tryUp(pos) == true)
//         dir[phant] = DIR_UP;
//       else if (tryDown(pos) == true)
//         dir[phant] = DIR_DOWN;
//       else
//         dir[phant] = WAIT;
//     }
//   }
//   else
//     dir[phant] = WAIT;
// }
//
// bool				Pacman::collision()
// {
//   for (size_t i = 0; i < this->phantom.size(); i++) {
//     Vector2<double>	tmp = this->phantom[i]->getPos();
//     if (this->pacman->getPos() == tmp)
//       return (true);
//     else if (tmp.x < 0 || tmp.x > WIDTH || tmp.y < 0 || tmp.y > HEIGHT)
//       newDir(phantom[i]);
//   }
//   return (false);
// }
//
// void				Pacman::phantom_compute(GameComponent *phant,
//                                                         std::stack<AComponent*>
//                                                         &comp)
// {
//   Vector2<double>			phantPos = phant->getPos();
//
//   comp.push(new GameComponent(phantPos, Vector2<double>(STEP, STEP), AComponent::BLACK,' ', "", GameComponent::CUBE_LARGE));
//   if (dir[phant] == WAIT)
//     dir[phant] = (direction)(rand() % WAIT);
//   switch (dir[phant]) {
//     case DIR_RIGHT:
//       phantPos.x += STEP;
//       break;
//     case DIR_LEFT:
//       phantPos.x -= STEP;
//       break;
//     case DIR_DOWN:
//       phantPos.y += STEP;
//       break;
//     case DIR_UP:
//       phantPos.y -= STEP;
//       break;
//     case WAIT:
//       break;
//   }
//   phant->setPos(phantPos);
// }
//
// std::stack<AComponent*>		Pacman::compute(int key)
// {
//   std::stack<AComponent*>	comp;
//   Vector2<double>			pacPos = this->pacman->getPos();
//
//   if ((dir[pacman] == WAIT && (key == ArcadeSystem::ArrowRight || key == ArcadeSystem::ArrowLeft || key == ArcadeSystem::ArrowDown || key == ArcadeSystem::ArrowUp))
//       || dir[pacman] != WAIT)
//     comp.push(new GameComponent(pacPos, Vector2<double>(STEP, STEP), AComponent::BLACK, ' ', "", GameComponent::CUBE_LARGE));
//   switch (key) {
//     case ArcadeSystem::ArrowRight:
//       dir[pacman] = DIR_RIGHT;
//       break;
//     case ArcadeSystem::ArrowLeft:
//       dir[pacman] = DIR_LEFT;
//       break;
//     case ArcadeSystem::ArrowDown:
//       dir[pacman] = DIR_DOWN;
//       break;
//     case ArcadeSystem::ArrowUp:
//       dir[pacman] = DIR_UP;
//       break;
//   }
//   switch (dir[pacman]) {
//     case DIR_RIGHT:
//       pacPos.x += STEP;
//       break;
//     case DIR_LEFT:
//       pacPos.x -= STEP;
//       break;
//     case DIR_DOWN:
//       pacPos.y += STEP;
//       break;
//     case DIR_UP:
//       pacPos.y -= STEP;
//       break;
//     case WAIT:
//       break;
//   }
//   if (collision() == true)
//     {
//       for (size_t i = 0; i < phantom.size(); i++) {
//         comp.push(new GameComponent(phantom[i]->getPos(), Vector2<double>(STEP, STEP), AComponent::BLACK, ' ', "", GameComponent::CUBE_LARGE));
//       }
//       phantom.clear();
//       restart();
//     }
//   else if (limit(pacPos) == false)
//     this->pacman->setPos(pacPos);
//   else
//     {
//       comp.pop();
//       dir[pacman] = WAIT;
//     }
//   comp.push(this->pacman);
//   for (size_t i = 0; i < this->phantom.size(); i++) {
//     this->phantom_compute(this->phantom[i], comp);
//     comp.push(this->phantom[i]);
//   }
//   return (comp);
// }
//
// std::stack<AComponent*>		Pacman::getInfos()
// {
//   std::stack<AComponent*>	comp;
//
//   return (comp);
// }
