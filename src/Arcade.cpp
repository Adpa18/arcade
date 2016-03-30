#include "Arcade.hpp"

arcade::Arcade::Arcade()
{
    this->refresh_lib("./lib/", GRAPH);
    this->refresh_lib("./games/", GAME);
}

arcade::Arcade::~Arcade(){}

void arcade::Arcade::refresh_lib(std::string const &folder, SOTYPE type)
{
    DIR           *dir;
    struct dirent *ent;

    if ((dir = opendir(folder.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (std::string(ent->d_name).find(".so") == std::string::npos)
            continue;
            if (type == GRAPH) {
                this->graphsNames.push_back(ent->d_name);
                initSo(folder + ent->d_name, GRAPH);

            } else {
                this->gamesNames.push_back(ent->d_name);
                initSo(folder + ent->d_name, GAME);
            }
        }
    } else {
        perror ("");
    }
}

void	arcade::Arcade::initSo(std::string const &name, SOTYPE type)
{
    void          *myso;
    const char    *dlsym_error;
    const char    *symbol;
    bool					has_init;

    has_init = true;
    if (type != GAME && type != GRAPH)
      std::runtime_error("Type Error");
    dlerror();
    if (name.find(".so") == std::string::npos)
    {
        myso = dlopen(std::string("./" +
        ((type == GAME)?std::string("games"):std::string("lib")) +
        "/lib_arcade_" + name + ".so").c_str(), RTLD_NOW | RTLD_GLOBAL);
    }
    else
      myso = dlopen(name.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (!myso)
        std::runtime_error(std::string("Cannot open library: ") + dlerror());
    symbol = (type == GAME) ? "loadGame" : "loadLib";
    fptr load = (void *(*)())(dlsym(myso, symbol));
    if ((dlsym_error = dlerror()))
      std::runtime_error(std::string("Cannot load symbol '") + symbol + "': " + dlsym_error);
    this->libs.push(myso);
    //check if init exist
    if (type == GRAPH)
    {
      f_init ini = (void *(*)(IGraph *, const std::string &, Vector2<double>, std::stack<AComponent*>))(dlsym(myso, "initLib"));
      if ((dlsym_error = dlerror())) {
        (void)ini;
        has_init = false;
      }
      f_destroy dest = (void *(*)(IGraph *))(dlsym(myso, "destroyLib"));
      if ((dlsym_error = dlerror()))
      {
        (void)dest;
        has_init = false;
      }
      if (has_init)
        this->graphs.push_back(std::pair<fptr, bool>(load, true));
      else
        this->graphs.push_back(std::pair<fptr, bool>(load, false));
    }
    else
      this->games.push_back(static_cast<AGame *>(load()));
}

void		arcade::Arcade::clean()
{
  while (!this->libs.empty())
  {
    dlclose(this->libs.top());
    this->libs.pop();
  }
}

bool    arcade::Arcade::run(const std::string &graphPath)
{
    int			key;
    int			graphPos;
    int			gamePos;
    IGraph	*graph;

    graphPos = find(this->graphsNames.begin(), this->graphsNames.end(), graphPath.substr(graphPath.find_last_of('/') + 1, graphPath.length())) - this->graphsNames.begin();
    gamePos = 0;
    graph = static_cast<IGraph *>(graphs[graphPos].first());
    if (graphs[graphPos].second)
      graph->init(games[gamePos]->getName(), games[gamePos]->getSize(), games[gamePos]->getInfos());
    std::chrono::milliseconds interval(60);
    GameLoop:
        if ((key = graph->eventManagment()) == ArcadeSystem::Exit) {
            return (true);
        } else if (key == ArcadeSystem::PrevGraph || key == ArcadeSystem::NextGraph
           || key == ArcadeSystem::PrevGame || key == ArcadeSystem::NextGame) {
            if (graphs[graphPos].second)
              graph->destroy();
            else
              delete graph;
            if (key == ArcadeSystem::PrevGraph) {
                --graphPos;
            } else if (key == ArcadeSystem::NextGraph) {
                ++graphPos;
            } else if (key == ArcadeSystem::PrevGame) {
                --gamePos;
            } else if (key == ArcadeSystem::NextGame) {
                ++gamePos;
            }
            graphPos = (graphPos < 0) ? graphsNames.size() - 1 : graphPos % graphsNames.size();
            gamePos = (gamePos < 0) ? gamesNames.size() - 1 : gamePos % gamesNames.size();
            graph = static_cast<IGraph *>(graphs[graphPos].first());
            if (graphs[graphPos].second)
              graph->init(games[gamePos]->getName(), games[gamePos]->getSize(), games[gamePos]->getInfos());
        }
        graph->display(games[gamePos]->compute(key));
        std::this_thread::sleep_for(interval);
    goto GameLoop;
    return (true);
}

int	main(int ac, char **av)
{
    arcade::Arcade  *arcade;

    if (ac < 2) {
        ERROR(USAGE, 1);
    }
    arcade = new arcade::Arcade();
    arcade->run(av[1]);
    arcade->clean();
    return (0);
}
