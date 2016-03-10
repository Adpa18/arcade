/*
** Arcade.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:28:59 2016 Nicolas Constanty
** Last update	Thu Mar 10 14:36:19 2016 Nicolas Constanty
*/

#include <iostream>
#include "Arcade.hpp"

arcade::Arcade::Arcade()
{
  this->refresh_lib("./lib/");
  this->refresh_lib("./games/");
}

arcade::Arcade::~Arcade()
{}

void arcade::Arcade::refresh_lib(std::string const &folder)
{
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (folder.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (std::string(ent->d_name).find(".so") != std::string::npos)
      {
        if (std::find(this->game_paths.begin(), this->game_paths.end(), ent->d_name) != this->game_paths.end())
          this->game_paths.push_back(ent->d_name);
      }
    }
  } else {
    perror ("");
  }
}

IGraph *arcade::Arcade::initGraph(void *ptr)
{
  const char *lib_name = "loadLib";
  typedef IGraph *(*fptr)();
  fptr load_lib = (IGraph *(*)())(dlsym(ptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  else
    return ((IGraph *)load_lib());
  return (NULL);
}

IGame *arcade::Arcade::initGame(void *ptr)
{
  const char *lib_name = "loadGame";
  typedef IGame *(*fptr)();
  fptr load_game = (IGame *(*)())(dlsym(ptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  else
    return ((IGame *)load_game());
  return (NULL);
}

void	*arcade::Arcade::initSo(std::string const &name, SOTYPE type)
{
  //reset error
  dlerror();
  void *myso;
  if (name.find(".so") == std::string::npos)
  {
    myso = dlopen(std::string("./" +
    ((type == GAME)?std::string("games"):std::string("lib")) +
    "/lib_arcade_" + name + ".so").c_str(), RTLD_LAZY | RTLD_GLOBAL);
  }
  else
    myso = dlopen(name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
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
  if (ac < 2)
  {
    std::cout << "USAGE : ./arcade [LIB_PATH.so]" << std::endl;
    return (1);
  }
  arcade::Arcade *arcade = new arcade::Arcade();
  IGraph *graph = (IGraph *)arcade->initSo(av[1], GRAPH);
  if (!graph)
    return (1);
  IGame *game = (IGame *)arcade->initSo("snake", GAME);
  if (!game)
    return (1);
  int	key;
  std::chrono::milliseconds interval(250);
GameLoop:
    key = graph->eventManagment();
    graph->display(game->compute(key));
    std::this_thread::sleep_for(interval) ;
    goto GameLoop;
  return (0);
}
