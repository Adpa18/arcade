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
    std::pair<void *, bool> *tmp;

    if ((dir = opendir(folder.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (std::string(ent->d_name).find(".so") == std::string::npos)
            continue;
            if (type == GRAPH) {
                this->graphsNames.push_back(ent->d_name);
                tmp = initSo(folder + ent->d_name, GRAPH);
                this->graphs.push_back(std::pair<IGraph *, bool>(static_cast<IGraph *>(tmp->first), tmp->second));
            } else {
                this->gamesNames.push_back(ent->d_name);
                tmp = initSo(folder + ent->d_name, GAME);
                this->games.push_back(static_cast<AGame *>(tmp->first));
            }
        }
    } else {
        perror ("");
    }
}

std::pair<void *, bool> *arcade::Arcade::initSo(std::string const &name, SOTYPE type)
{
    void          *myso;
    const char    *dlsym_error;
    const char    *symbol;
    typedef void  *(*fptr)();
    typedef void  *(*f_init)(IGraph *, const std::string &, Vector2<double>, std::stack<AComponent*>);
    typedef void  *(*f_destroy)(IGraph *);
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
      return (new std::pair<void *, bool>(load(), true));
  return (new std::pair<void *, bool>(load(), false));
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
    int	   key;
    int    graphPos;
    int    gamePos;

    graphPos = find(this->graphsNames.begin(), this->graphsNames.end(), graphPath.substr(graphPath.find_last_of('/') + 1, graphPath.length())) - this->graphsNames.begin();
    gamePos = 0;
    if (graphs[graphPos].second)
      graphs[graphPos].first->init(games[gamePos]->getName(), games[gamePos]->getSize(), games[gamePos]->getInfos());
    std::chrono::milliseconds interval(600);
    GameLoop:
        if ((key = graphs[graphPos].first->eventManagment()) == ArcadeSystem::Exit) {
            return (true);
        } else if (key == ArcadeSystem::PrevGraph || key == ArcadeSystem::NextGraph
           || key == ArcadeSystem::PrevGame || key == ArcadeSystem::NextGame) {
            if (graphs[graphPos].second)
              graphs[graphPos].first->destroy();
            else
              delete graphs[graphPos].first;
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
            if (graphs[graphPos].second)
              graphs[graphPos].first->init(games[gamePos]->getName(), games[gamePos]->getSize(), games[gamePos]->getInfos());
            else
              graphs[graphPos].first = static_cast<IGraph *>(initSo(graphsNames[graphPos], GRAPH)->first);
        }
        graphs[graphPos].first->display(games[gamePos]->compute(key));
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
    // arcade->clean();
    return (0);
}
