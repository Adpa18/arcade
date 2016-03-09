/*
** Arcade.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:23:04 2016 Nicolas Constanty
** Last update	Wed Mar 09 16:53:01 2016 Nicolas Constanty
*/

#ifndef ARCADE_HPP_
# define ARCADE_HPP_

# include <dlfcn.h>
# include "Utils.hpp"
# include "Interfaces.hpp"

enum SOTYPE { GRAPH, GAME };

class Arcade {
public:
  Arcade ();
  virtual ~Arcade ();
  static void* initSo(std::string const &, SOTYPE);
  static IGame*  initGame(void *ptr);
  static IGraph* initGraph(void *ptr);
};

#endif /* !ARCADE_HPP_ */
