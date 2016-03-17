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

  // static const int winWidth = 50;
  // static const int winHeight = 30;

  class Arcade {
  private:
    std::vector<IGraph *>       graphs;
    std::vector<AGame *>        games;
    std::vector<std::string>    graphsNames;
    std::vector<std::string>    gamesNames;
  public:
    Arcade ();
    virtual ~Arcade ();
    bool    run(const std::string &graph);
    void    *initSo(std::string const &, SOTYPE);
    void    refresh_lib(std::string const &folder, SOTYPE);
  };
}

#endif /* !ARCADE_HPP_ */
