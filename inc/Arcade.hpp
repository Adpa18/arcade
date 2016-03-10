/*
** Arcade.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:23:04 2016 Nicolas Constanty
<<<<<<< HEAD
** Last update	Thu Mar 10 14:29:34 2016 Nicolas Constanty
=======
** Last update	Thu Mar 10 15:35:56 2016 Adrien WERY
>>>>>>> eb8433b0cda9a6713033fe09981c0dae98436182
*/

#ifndef ARCADE_HPP_
# define ARCADE_HPP_

# include <dlfcn.h>
# include <vector>
# include <dirent.h>
# include <stdio.h>
# include <unistd.h>
# include <algorithm>
# include <chrono>
# include <thread>
# include <iostream>
# include "Utils.hpp"
# include "Interfaces.hpp"

enum SOTYPE { GRAPH, GAME };

# define USAGE "USAGE : ./arcade [LIB_PATH.so]"
# define ERROR(msg, ret) ({std::cerr << msg << std::endl;return (ret);})

namespace arcade {

  static const int winWidth = 50;
  static const int winHeight = 30;

  class Arcade {
  private:
    std::vector<std::string> graph_paths;
    std::vector<std::string> game_paths;
  public:
    Arcade ();
    virtual ~Arcade ();
    void    *initSo(std::string const &, SOTYPE);
    void    refresh_lib(std::string const &folder);
  };
}

#endif /* !ARCADE_HPP_ */
