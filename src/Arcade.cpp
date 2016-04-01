#include "Arcade.hpp"

arcade::Arcade::Arcade()
{
    this->refresh_lib("./lib/", GRAPH);
    this->refresh_lib("./games/", GAME);
    this->_status = Menu;
    this->graphPos = 0;
    this->gamePos = 0;
    this->graph = NULL;
    this->game = NULL;
    this->isPaused = false;
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

void    arcade::Arcade::changeGraph(int key)
{
    if (this->graph) {
        delete (this->graph);
    }
    this->graphPos += (key == ArcadeSystem::PrevGraph) ? -1 : 1;
    this->graphPos = (this->graphPos < 0) ? this->graphsNames.size() - 1 : this->graphPos % this->graphsNames.size();
    this->graph = static_cast<IGraph *>(this->graphs[this->graphPos]());
    this->graph->setTitle(this->game->getName());
}

void    arcade::Arcade::changeGame(int key)
{
    if (this->game) {
        delete (this->game);
    }
    this->gamePos += (key == ArcadeSystem::PrevGame) ? -1 : 1;
    this->gamePos = (this->gamePos < 0) ? this->gamesNames.size() - 1 : this->gamePos % this->gamesNames.size();
    this->game = static_cast<IGame *>(this->games[this->gamePos]());
    this->graph->setTitle(this->game->getName());
}


bool    arcade::Arcade::run(const std::string &graphPath)
{
    std::stack<AComponent*> components;
    UIComponent *pauseUI;
    UIComponent *gamesUI[this->gamesNames.size()];
    int     key;

    if ((graphPos = find(this->graphsNames.begin(), this->graphsNames.end(), graphPath.substr(graphPath.find_last_of('/') + 1, graphPath.length())) - this->graphsNames.begin()) == (int)this->graphsNames.size()) {
        return (false);
    }
    pauseUI = new UIComponent(Vector2<double>(ArcadeSystem::winWidth / 2, ArcadeSystem::winHeight / 2), AComponent::WHITE, Vector2<double>(0, 0), "Pause");
    for (size_t i = 0; i < this->gamesNames.size(); i++) {
        gamesUI[i] = new UIComponent(Vector2<double>(ArcadeSystem::winWidth / 2, i + ArcadeSystem::winHeight / 2 - this->gamesNames.size() / 2), AComponent::WHITE, Vector2<double>(0, 0), this->gamesNames[i].substr(11, this->gamesNames[i].length() -14));
    }
    this->graph = static_cast<IGraph *>(this->graphs[graphPos]());
    this->game = static_cast<IGame *>(this->games[this->gamePos]());
    this->graph->setTitle(this->game->getName());
    std::chrono::milliseconds interval(60);
    GameLoop:
        key = this->graph->eventManagment();
        switch (key) {
            case ArcadeSystem::Exit:
                return (true);
            case ArcadeSystem::Home:
                this->_status = Menu;
                break;
            case ArcadeSystem::Pause:
                this->isPaused = !this->isPaused;
                break;
            case ArcadeSystem::PrevGraph:
            case ArcadeSystem::NextGraph:
                this->changeGraph(key);
                break;
            case ArcadeSystem::PrevGame:
            case ArcadeSystem::NextGame:
                this->changeGame(key);
                break;
        }
        if (this->_status == Menu && key == ArcadeSystem::Enter) {
            this->_status = Game;
        }
        if (this->isPaused) {
            components.push(pauseUI);
        } else if (this->_status == Game) {
            components = game->compute(key);
        } else if (this->_status == Menu) {
            if (key == ArcadeSystem::ArrowUp) {
                this->changeGame(ArcadeSystem::PrevGame);
            } else if (key == ArcadeSystem::ArrowDown) {
                this->changeGame(ArcadeSystem::NextGame);
            }
            for (size_t i = 0; i < this->gamesNames.size(); i++) {
                gamesUI[i]->setColor((this->gamePos == (int)i) ? AComponent::RED : AComponent::WHITE);
                components.push(gamesUI[i]);
            }
        }
        graph->display(components);
        while (!components.empty()) {
            components.pop();
        }
        std::this_thread::sleep_for(interval);
    goto GameLoop;
    return (true);
}

void		arcade::Arcade::clean()
{
    if (this->graph)
        delete (this->graph);
    if (this->game)
        delete (this->game);
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
