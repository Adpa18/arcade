/*
** Arcade.cpp for cpp_arcade
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Mar 16 21:49:22 2016 Adrien WERY
** Last update	Thu Mar 17 16:12:52 2016 Adrien WERY
*/

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
            std::cout << ent->d_name << std::endl;
            if (type == GRAPH) {
                this->graphsNames.push_back(ent->d_name);
                this->graphs.push_back((IGraph *)initSo(folder + ent->d_name, GRAPH));
            } else {
                this->gamesNames.push_back(ent->d_name);
                this->games.push_back((AGame *)initSo(folder + ent->d_name, GAME));
            }
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
    else {
        myso = dlopen(name.c_str(), RTLD_NOW | RTLD_GLOBAL);
    }
    if (!myso) {
        ERROR("Cannot open library: " << dlerror(), NULL);
    }
    symbol = (type == GAME) ? "loadGame" : "loadLib";
    fptr load = (void *(*)())(dlsym(myso, symbol));
    if ((dlsym_error = dlerror())) {
        ERROR("Cannot load symbol '" << symbol << "': " << dlsym_error, NULL);
    }
    return (load());
}

bool    arcade::Arcade::run(const std::string &graphPath)
{
    int	            key;
    unsigned int    graphPos;
    unsigned int    gamePos;

    graphPos = find(this->graphsNames.begin(), this->graphsNames.end(), graphPath.substr(graphPath.find_last_of('/') + 1, graphPath.length())) - this->graphsNames.begin();
    gamePos = 0;
    graphs[graphPos]->init(games[gamePos]->getName(), games[gamePos]->getSize(), games[gamePos]->getInfos());
    std::chrono::milliseconds interval(60);
    GameLoop:
        if ((key = graphs[graphPos]->eventManagment()) == ESC) {
            return (true);
        } else if (key == KEY_2) {
            --graphPos;
        } else if (key == KEY_3) {
            ++graphPos;
        } else if (key == KEY_4) {
            --gamePos;
        } else if (key == KEY_5) {
            ++gamePos;
        }
        if (key == KEY_2 || key == KEY_3 || key == KEY_3 || key == KEY_4) {
            graphs[graphPos]->init(games[gamePos]->getName(), games[gamePos]->getSize(),
            games[gamePos]->getInfos());
        }
        graphs[graphPos]->display(games[gamePos]->compute(key));
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
    return (arcade->run(av[1]));
}
