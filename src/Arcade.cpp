/*
** Arcade.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:28:59 2016 Nicolas Constanty
** Last update	Wed Mar 09 16:54:51 2016 Nicolas Constanty
*/

#include <iostream>
#include "Arcade.hpp"

IGraph *Arcade::initGraph(void *ptr)
{
  std::cout << "StartInit => Graph" << std::endl;
  const char *lib_name = "_Z7loadLibv";
  typedef IGraph *(*fptr)();
  fptr load_lib = (IGraph *(*)())(dlsym(ptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
  {
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  }
  else
  {
    return ((IGraph *)load_lib());
  }
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
  {
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  }
  else
  {
    return ((IGame *)load_game());
  }
  std::cout << "EndInit => Game" << std::endl;
  return (NULL);
}

void	*Arcade::initSo(std::string const &name, SOTYPE type)
{
  //reset error
  dlerror();
  void *myso = dlopen(std::string("./" +
    ((type == GAME)?std::string("games"):std::string("lib")) +
    "/lib_arcade_" + name + ".so").c_str(), RTLD_LAZY);
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

int	main()
{

  IGraph *graph = (IGraph *)Arcade::initSo("ncurses", GRAPH);
  IGame *game = (IGame *)Arcade::initSo("snake", GAME);
  (void)game;
  (void)graph;
  return (0);
}
