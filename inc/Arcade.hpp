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

  class Arcade {
  private:
    std::vector<std::pair<IGraph *, bool>>  graphs;
    std::vector<AGame *>                    games;
    std::stack<void *>                      libs;
    std::vector<std::string>                graphsNames;
    std::vector<std::string>                gamesNames;
  public:
    Arcade ();
    virtual ~Arcade ();
    bool    run(const std::string &graph);
    std::pair<void *, bool>    *initSo(std::string const &, SOTYPE);
    void    refresh_lib(std::string const &folder, SOTYPE);
    void		clean();
  };
}

#endif /* !ARCADE_HPP_ */
