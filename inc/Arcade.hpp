/*
** Arcade.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:23:04 2016 Nicolas Constanty
** Last update	Wed Mar 09 18:25:07 2016 Nicolas Constanty
*/

#ifndef ARCADE_HPP_
# define ARCADE_HPP_

# include <dlfcn.h>
# include <vector>
#include <dirent.h>
#include <stdio.h>
#include <algorithm>
# include "Utils.hpp"
# include "Interfaces.hpp"

enum SOTYPE { GRAPH, GAME };

class Arcade {
private:
  std::vector<std::string> graph_paths;
  std::vector<std::string> game_paths;
public:
  Arcade ();
  virtual ~Arcade ();
  void* initSo(std::string const &, SOTYPE);
  IGame*  initGame(void *ptr);
  IGraph* initGraph(void *ptr);
  void		refresh_lib(std::string const &folder);
};

#endif /* !ARCADE_HPP_ */
