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
    closedir(dir);
}

void	arcade::Arcade::initSo(std::string const &name, SOTYPE type)
{
    void          *myso;
    const char    *dlsym_error;
    const char    *symbol;

    if (type != GAME && type != GRAPH)
      std::runtime_error("Type Error");
    dlerror();
    myso = dlopen(name.c_str(), RTLD_NOW);
    if (!myso || (dlsym_error = dlerror())) {
        std::runtime_error(std::string("Cannot open library: ") + dlerror());
    }
    symbol = (type == GAME) ? "loadGame" : "loadLib";
    fptr load = (void *(*)())(dlsym(myso, symbol));
    if ((dlsym_error = dlerror())) {
        std::runtime_error(std::string("Cannot load symbol '") + symbol + "': " + dlsym_error);
    }
    this->libs.push(myso);
    if (type == GRAPH) {
        this->graphs.push_back(load);
    } else {
        this->games.push_back(load);
    }
}

bool    arcade::Arcade::run(const std::string &graphPath)
{
    IGraph  *graph;
    IGame   *game;
    int     key;
    int		graphPos;
    int		gamePos;

    if ((graphPos = find(this->graphsNames.begin(), this->graphsNames.end(), graphPath.substr(graphPath.find_last_of('/') + 1, graphPath.length())) - this->graphsNames.begin()) == (int)this->graphsNames.size()) {
        return (false);
    }
    gamePos = 1;
    graph = static_cast<IGraph *>(graphs[graphPos]());
    game = NULL;
    // tmp
    game = static_cast<IGame *>(games[gamePos]());
    graph->setTitle(game->getName());
    // tmp
    std::chrono::milliseconds interval(60);
    GameLoop:
        if ((key = graph->eventManagment()) == ArcadeSystem::Exit) {
            if (graph)
                delete (graph);
            if (game)
                delete (game);
            return (true);
        } else if (key == ArcadeSystem::PrevGraph || key == ArcadeSystem::NextGraph) {
            if (key == ArcadeSystem::PrevGraph) {
                --graphPos;
            } else if (key == ArcadeSystem::NextGraph) {
                ++graphPos;
            }
            if (graph)
                delete (graph);
            graphPos = (graphPos < 0) ? graphsNames.size() - 1 : graphPos % graphsNames.size();
            graph = static_cast<IGraph *>(graphs[graphPos]());
            graph->setTitle(game->getName());
        } else if (key == ArcadeSystem::PrevGame || key == ArcadeSystem::NextGame) {
            if (key == ArcadeSystem::PrevGame) {
                --gamePos;
            } else if (key == ArcadeSystem::NextGame) {
                ++gamePos;
            }
            if (game)
                delete (game);
            gamePos = (gamePos < 0) ? gamesNames.size() - 1 : gamePos % gamesNames.size();
            game = static_cast<IGame *>(games[gamePos]());
            graph->setTitle(game->getName());
        }
        graph->display(game->compute(key));
        std::this_thread::sleep_for(interval);
    goto GameLoop;
    return (true);
}

void		arcade::Arcade::clean()
{
    while (!this->libs.empty())
    {
        dlclose(this->libs.top());
        this->libs.pop();
    }
}

int	main(int ac, char **av)
{
    arcade::Arcade  *arcade;

    if (ac < 2) {
        ERROR(USAGE, 1);
    }
    arcade = new arcade::Arcade();
    if (!arcade->run(av[1])) {
        ERROR(USAGE, 1);
    }
    arcade->clean();
    return (0);
}
