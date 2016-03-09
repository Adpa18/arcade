/*
** Arcade.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:28:59 2016 Nicolas Constanty
** Last update	Wed Mar 09 18:26:59 2016 Nicolas Constanty
*/

#include <iostream>
#include "Arcade.hpp"

Arcade::Arcade()
{
  this->refresh_lib("./lib/");
  this->refresh_lib("./games/");
}

Arcade::~Arcade()
{}

void Arcade::refresh_lib(std::string const &folder)
{
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (folder.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (std::string(ent->d_name).find(".so") != std::string::npos)
      {
        std::cout << ent->d_name << std::endl;
        if (std::find(this->game_paths.begin(), this->game_paths.end(), ent->d_name) != this->game_paths.end())
          this->game_paths.push_back(ent->d_name);
      }
    }
  } else {
    perror ("");
  }
}

IGraph *Arcade::initGraph(void *ptr)
{
  std::cout << "StartInit => Graph" << std::endl;
  const char *lib_name = "_Z7loadLibv";
  typedef IGraph *(*fptr)();
  fptr load_lib = (IGraph *(*)())(dlsym(ptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  else
    return ((IGraph *)load_lib());
  std::cout << "EndInit => Graph" << std::endl;
  return (NULL);
}

IGame *Arcade::initGame(void *ptr)
{
  std::cout << "StartInit => Game" << std::endl;
  const char *lib_name = "_Z8loadGamev";
  typedef IGame *(*fptr)();
  fptr load_game = (IGame *(*)())(dlsym(ptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  else
    return ((IGame *)load_game());
  std::cout << "EndInit => Game" << std::endl;
  return (NULL);
}

void	*Arcade::initSo(std::string const &name, SOTYPE type)
{
  //reset error
  dlerror();
  void *myso;
  if (name.find(".so") == std::string::npos)
  {
    myso = dlopen(std::string("./" +
    ((type == GAME)?std::string("games"):std::string("lib")) +
    "/lib_arcade_" + name + ".so").c_str(), RTLD_LAZY);
  }
  else
    myso = dlopen(name.c_str(), RTLD_LAZY);
  if (!myso)
  {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return (NULL);
  }
  if (type == GAME)
    return Arcade::initGame(myso);
  else if (type == GRAPH)
    return Arcade::initGraph(myso);
  return (NULL);
}

int	main(int ac, char **av)
{
  //Make usage
  if (ac < 2)
  {
    std::cout << "USAGE : ./arcade [LIB_PATH.so]" << std::endl;
    return (1);
  }
  Arcade *arcade = new Arcade();
  IGraph *graph = (IGraph *)arcade->initSo(av[1], GRAPH);
  IGame *game = (IGame *)arcade->initSo("snake", GAME);
  (void)game;
  (void)graph;
  return (0);
}
