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
# include "Vector2.hpp"
# include "IGame.hpp"
# include "IGraph.hpp"
# include "UIComponent.hpp"
# include "ArcadeSystem.hpp"

enum SOTYPE { GRAPH, GAME };
enum Status { Game, Menu };

# define USAGE "USAGE : ./arcade [LIB_PATH.so]"
# define ERROR(msg, ret) ({std::cerr << msg << std::endl;return (ret);})

namespace arcade {

  class Arcade {
  private:
    typedef void  *(*fptr)();
    bool                        isPaused;
    Status                      _status;
    std::vector<fptr>           graphs;
    std::vector<fptr>           games;
    std::vector<std::string>    graphsNames;
    std::vector<std::string>    gamesNames;
    std::stack<void *>          libs;
    IGraph                      *graph;
    IGame                       *game;
    int		                    graphPos;
    int		                    gamePos;
  public:
    Arcade ();
    virtual ~Arcade ();
    bool    run(const std::string &graphPath);
    void	initSo(std::string const &, SOTYPE);
    void    refresh_lib(std::string const &folder, SOTYPE);
    void    changeGraph(int key);
    void    changeGame(int key);
    void	clean();
  };
}

#endif /* !ARCADE_HPP_ */
