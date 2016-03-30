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
# include <map>
# include "Utils.hpp"
# include "Interfaces.hpp"

enum SOTYPE { GRAPH, GAME };

# define USAGE "USAGE : ./arcade [LIB_PATH.so]"
# define ERROR(msg, ret) ({std::cerr << msg << std::endl;return (ret);})

namespace arcade {

  class Arcade {
  private:
    typedef void  *(*fptr)();
    typedef void  *(*f_init)(IGraph *, const std::string &, Vector2<double>, std::stack<AComponent*>);
    typedef void  *(*f_destroy)(IGraph *);
    std::vector<std::pair<fptr, bool>>  		graphs;
    std::vector<AGame *>                    games;
    std::stack<void *>                      libs;
    std::vector<std::string>                graphsNames;
    std::vector<std::string>                gamesNames;
  public:
    Arcade ();
    virtual ~Arcade ();
    bool    run(const std::string &graph);
    void		initSo(std::string const &, SOTYPE);
    void    refresh_lib(std::string const &folder, SOTYPE);
    void		clean();
  };
}

#endif /* !ARCADE_HPP_ */
