/*
** Arcade.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:07 2016 Nicolas Constanty
** Last update	Wed Mar 16 21:34:09 2016 Nicolas Constanty
*/

#include "Arcade.hpp"

arcade::Arcade::Arcade()
{
  this->refresh_lib("./lib/");
  this->refresh_lib("./games/");
}

arcade::Arcade::~Arcade(){}

void arcade::Arcade::refresh_lib(std::string const &folder)
{
    DIR           *dir;
    struct dirent *ent;

    if ((dir = opendir (folder.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (std::string(ent->d_name).find(".so") == std::string::npos)
                continue;
            std::cout << ent->d_name << std::endl;
            if (std::find(this->game_paths.begin(), this->game_paths.end(),
                ent->d_name) != this->game_paths.end())
                this->game_paths.push_back(ent->d_name);
        }
    } else {
        perror ("");
    }
}

void	*arcade::Arcade::initSo(std::string const &name, SOTYPE type)
{
    void        *myso;
    const char  *dlsym_error;
    const char  * symbol;
    typedef void *(*fptr)();

    if (type != GAME && type != GRAPH)
        ERROR("Type Error", NULL);
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
        ERROR("Cannot open library: " << dlerror(), NULL);
    symbol = (type == GAME) ? "loadGame" : "loadLib";
    fptr load = (void *(*)())(dlsym(myso, symbol));
    if ((dlsym_error = dlerror()))
        ERROR("Cannot load symbol '" << symbol << "': " << dlsym_error, NULL);
    else
        return (load());
}

int	main(int ac, char **av)
{
    arcade::Arcade  *arcade;
    IGraph          *graph;
    AGame           *game;
    int	            key;

    if (ac < 2)
        ERROR(USAGE, 1);
    arcade = new arcade::Arcade();
    if (!(graph = (IGraph *)arcade->initSo(av[1], GRAPH)))
        return (1);
    if (!(game = (AGame *)arcade->initSo("snake", GAME)))
        return (1);
    std::chrono::milliseconds interval(60);
    graph->init(game->getName(), game->getSize(), game->getInfos());
    GameLoop:
        if ((key = graph->eventManagment()) == ESC)
            return (0);
        graph->display(game->compute(key));
        std::this_thread::sleep_for(interval);
        goto GameLoop;
  return (0);
}
