/*
** Ncurses.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 23:35:04 2016 Nicolas Constanty
** Last update	Wed Mar 16 22:20:30 2016 Adrien WERY
*/

#include <iostream>
#include "Ncurses.hpp"

using namespace ncurses;

Ncurses::Ncurses (void)
{
    std::cout << "StartInit => Lib Ncurses" << std::endl;
    int width = 50;
    int height = 30;

    initscr();
    cbreak();
    keypad(stdscr, true);
    start_color();
    curs_set(0);
    noecho();
    halfdelay(1);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    refresh();
    Vector2 size(width, height);
    Vector2 pos(COLS / 2 - (width / 2), LINES / 2 - (height / 2));
    if (this->invalidSize(width, height, size, pos) == false)
    {
        this->wind = new Window(size, pos, NULL);
        keypad(this->wind->getWind(), true);
        this->initMainWindow();
    }
    else
    this->wind = NULL;
}

Ncurses::~Ncurses ()
{
}

void	Ncurses::initMainWindow()
{
    wbkgd(this->wind->getWind(), COLOR_PAIR(3));
    wattr_on(this->wind->getWind(), A_REVERSE, NULL);
    wborder(this->wind->getWind(), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattr_off(this->wind->getWind(), A_REVERSE, NULL);
    wrefresh(this->wind->getWind());
}

bool	Ncurses::invalidSize(int width, int height, Vector2 const &size, Vector2 const &pos)
{
    if (pos.x + size.x > COLS -2 || pos.y + size.y > LINES - 1)
    {
        if (this->wind)
        {
            this->wind->close();
            this->wind = NULL;
        }
        this->valid_size = false;
        clear();
        mvprintw(LINES / 2, COLS / 2 -13, "Available size : %d x %d", COLS, LINES);
        mvprintw(LINES / 2 + 1, COLS / 2 - 12, "Required size : %d x %d", width, height);
        return (true);
    }
    this->valid_size = true;
    return (false);
}

int	Ncurses::resizeTerm()
{
    int width = 50;
    int height = 30;

    Vector2 size(width, height);
    Vector2 pos(COLS / 2 - (width / 2), LINES / 2 - (height / 2));
    if (!this->invalidSize(width, height, size, pos))
    {
        if (this->wind)
        {
            clear();
            refresh();
            mvwin(this->wind->getWind(), pos.y, pos.x);
            this->initMainWindow();
        }
        else
        {
            clear();
            refresh();
            this->wind = new Window(size, pos, NULL);
            keypad(this->wind->getWind(), true);
            this->initMainWindow();
        }
    }
    return (-2);
}

int Ncurses::eventManagment()
{
    int key;

    key = getch();
    if (key == KEY_RESIZE)
        return (this->resizeTerm());
    if (key == 27) {
        endwin();
    }
    return (this->keyMap[key]);
}

void Ncurses::display(std::stack<AComponent*> components)
{
    AComponent      *obj;
    GameComponent   *Gobj;

    if (this->valid_size == false)
        return;
    while (!components.empty()) {
        obj = components.top();
        components.pop();
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            wattron(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
            wattr_on(this->wind->getWind(), A_REVERSE, NULL);
            mvwaddch(this->wind->getWind(),
            Gobj->getPos().y, Gobj->getPos().x, Gobj->getSpriteText());
            wattr_off(this->wind->getWind(), A_REVERSE, NULL);
            wattroff(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
        }
    }
    wrefresh(this->wind->getWind());
    // if (this->valid_size == false)
    //   return;
    // while (!components.empty())
    // {
    //   GameComponent *object = dynamic_cast<GameComponent *>(components.top());
    //   if (object)
    //   {
    //     // printf("%d\n", this->wind->getPos().x + object->getPos().x);
    //     // if (object->getSpriteText() != ' ')
    //     // {
    //       wattron(this->wind->getWind(), COLOR_PAIR(object->getColor() + 1));
    //       wattr_on(this->wind->getWind(), A_REVERSE, NULL);
    //       mvwaddch(this->wind->getWind(),
    //       object->getPos().y,
    //       object->getPos().x,
    //       object->getSpriteText());
    //       wattr_off(this->wind->getWind(), A_REVERSE, NULL);
    //       wattroff(this->wind->getWind(), COLOR_PAIR(object->getColor() + 1));
    //     // }
    //     // else
    //     // {
    //     //   attron(COLOR_PAIR(object->getColor() + 1));
    //     //   mvwaddch(this->wind->getWind(),
    //     //   this->wind->getPos().x + object->getPos().x,
    //     //   this->wind->getPos().y + object->getPos().y,
    //     //   object->getSpriteText());
    //     //   attron(COLOR_PAIR(object->getColor() + 1));
    //     // }
    //     components.pop();
    //   }
    //   else
    //     components.pop();
    // }
}

void  Ncurses::init(const std::string &name, Vector2 size, std::stack<AComponent*> cache)
{
    (void)name;
    (void)size;
    this->display(cache);
}
