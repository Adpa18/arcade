/*
** Pacman.cpp for cpp_arcade
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Tue Mar 15 19:05:55 2016 Axel Vencatareddy
** Last update	Mon Mar 28 21:32:03 2016 Nicolas Constanty
*/

#include "Pacman.hpp"

Pacman::Pacman() : AGame("Pacman", Vector2<int>(WIDTH, HEIGHT))
{
  this->restart();
}

Pacman::~Pacman()
{}

bool				Pacman::limit(Vector2<int> tmp)
{
  if (tmp.x < 0 || tmp.x >= WIDTH || tmp.y < 0 || tmp.y >= HEIGHT)
    return (true);
  else
    return (false);
}

bool				Pacman::tryDown(Vector2<int> pos)
{
  if (pos.y + STEP >= HEIGHT)
    return (false);
  else
    return (true);
}

bool				Pacman::tryUp(Vector2<int> pos)
{
  if (pos.y - STEP <= 0)
    return (false);
  else
    return (true);
}

bool				Pacman::tryRight(Vector2<int> pos)
{
  if (pos.x + STEP >= WIDTH)
    return (false);
  else
    return (true);
}

bool				Pacman::tryLeft(Vector2<int> pos)
{
  if (pos.x - STEP <= 0)
    return (false);
  else
    return (true);
}

void				Pacman::newDir(GameComponent *phant)
{
  direction			save;
  Vector2<int>			pos = phant->getPos();
  int				aleat;

  save = dir[phant];
  aleat = rand() % 2;
  if (save == DIR_LEFT || save == DIR_RIGHT) {
    if (aleat == 0) {
      if (tryDown(pos) == true)
        dir[phant] = DIR_DOWN;
      else if (tryUp(pos) == true)
        dir[phant] = DIR_UP;
      else if (tryLeft(pos) == true)
        dir[phant] = DIR_LEFT;
      else if (tryRight(pos) == true)
        dir[phant] = DIR_RIGHT;
      else
        dir[phant] = WAIT;
    }
    else {
      if (tryUp(pos) == true)
        dir[phant] = DIR_UP;
      else if (tryDown(pos) == true)
        dir[phant] = DIR_DOWN;
      else if (tryRight(pos) == true)
        dir[phant] = DIR_RIGHT;
      else if (tryLeft(pos) == true)
        dir[phant] = DIR_LEFT;
      else
        dir[phant] = WAIT;
    }
  }
  else if (save == DIR_DOWN || save == DIR_UP) {
    if (aleat == 0) {
      if (tryLeft(pos) == true)
        dir[phant] = DIR_LEFT;
      else if (tryRight(pos) == true)
        dir[phant] = DIR_RIGHT;
      else if (tryDown(pos) == true)
        dir[phant] = DIR_DOWN;
      else if (tryUp(pos) == true)
        dir[phant] = DIR_UP;
      else
        dir[phant] = WAIT;
    }
    else {
      if (tryRight(pos) == true)
        dir[phant] = DIR_RIGHT;
      else if (tryLeft(pos) == true)
        dir[phant] = DIR_LEFT;
      else if (tryUp(pos) == true)
        dir[phant] = DIR_UP;
      else if (tryDown(pos) == true)
        dir[phant] = DIR_DOWN;
      else
        dir[phant] = WAIT;
    }
  }
  else
    dir[phant] = WAIT;
}

bool				Pacman::collision()
{
  for (size_t i = 0; i < this->phantom.size(); i++) {
    Vector2<int>	tmp = this->phantom[i]->getPos();
    if (this->pacman->getPos() == tmp)
      return (true);
    else if (tmp.x < 0 || tmp.x > WIDTH || tmp.y < 0 || tmp.y > HEIGHT)
      newDir(phantom[i]);
  }
  return (false);
}

void				Pacman::phantom_compute(GameComponent *phant,
                                                        std::stack<AComponent*>
                                                        &comp)
{
  Vector2<int>			phantPos = phant->getPos();

  comp.push(new GameComponent(phantPos, Vector2<int>(STEP, STEP), BLACK,' ', "", NULL));
  if (dir[phant] == WAIT)
    dir[phant] = (direction)(rand() % WAIT);
  switch (dir[phant]) {
    case DIR_RIGHT:
      phantPos.x += STEP;
      break;
    case DIR_LEFT:
      phantPos.x -= STEP;
      break;
    case DIR_DOWN:
      phantPos.y += STEP;
      break;
    case DIR_UP:
      phantPos.y -= STEP;
      break;
    case WAIT:
      break;
  }
  phant->setPos(phantPos);
}

std::stack<AComponent*>		Pacman::compute(int key)
{
  std::stack<AComponent*>	comp;
  Vector2<int>			pacPos = this->pacman->getPos();

  if ((dir[pacman] == WAIT && (key == RIGHT || key == LEFT || key == DOWN || key == UP))
      || dir[pacman] != WAIT)
    comp.push(new GameComponent(pacPos, Vector2<int>(STEP, STEP), BLACK, ' ', "", NULL));
  switch (key) {
    case RIGHT:
      dir[pacman] = DIR_RIGHT;
      break;
    case LEFT:
      dir[pacman] = DIR_LEFT;
      break;
    case DOWN:
      dir[pacman] = DIR_DOWN;
      break;
    case UP:
      dir[pacman] = DIR_UP;
      break;
  }
  switch (dir[pacman]) {
    case DIR_RIGHT:
      pacPos.x += STEP;
      break;
    case DIR_LEFT:
      pacPos.x -= STEP;
      break;
    case DIR_DOWN:
      pacPos.y += STEP;
      break;
    case DIR_UP:
      pacPos.y -= STEP;
      break;
    case WAIT:
      break;
  }
  if (collision() == true)
    {
      for (size_t i = 0; i < phantom.size(); i++) {
        comp.push(new GameComponent(phantom[i]->getPos(), Vector2<int>(STEP, STEP), BLACK, ' ', "", NULL));
      }
      phantom.clear();
      restart();
    }
  else if (limit(pacPos) == false)
    this->pacman->setPos(pacPos);
  else
    {
      comp.pop();
      dir[pacman] = WAIT;
    }
  comp.push(this->pacman);
  for (size_t i = 0; i < this->phantom.size(); i++) {
    this->phantom_compute(this->phantom[i], comp);
    comp.push(this->phantom[i]);
  }
  return (comp);
}

std::stack<AComponent*>		Pacman::getInfos()
{
  std::stack<AComponent*>	comp;

  return (comp);
}

void				Pacman::restart()
{
  this->pacman = new GameComponent(Vector2<int>(0, 0), Vector2<int>(STEP, STEP), YELLOW, ' ', "", NULL);
  this->phantom.push_back(new GameComponent(Vector2<int>(60, 60), Vector2<int>(STEP, STEP), GREEN, ' ', "", NULL));
  this->phantom.push_back(new GameComponent(Vector2<int>(80, 80), Vector2<int>(STEP, STEP), RED, ' ', "", NULL));
  this->phantom.push_back(new GameComponent(Vector2<int>(100, 100), Vector2<int>(STEP, STEP), CYAN, ' ', "", NULL));
  this->phantom.push_back(new GameComponent(Vector2<int>(120, 120), Vector2<int>(STEP, STEP), WHITE, ' ', "", NULL));
  this->dir[pacman] = WAIT;
  for (size_t i = 0; i < this->phantom.size(); i++) {
    this->dir[phantom[i]] = WAIT;
  }
}
