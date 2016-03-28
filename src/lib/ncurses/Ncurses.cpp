#include <iostream>
#include "Ncurses.hpp"

using namespace ncurses;

Ncurses::Ncurses (void) : size(0, 0)
{
}

Ncurses::~Ncurses ()
{
}

void	Ncurses::initMainWindow()
{
    wbkgd(this->main_wind->getWind(), COLOR_PAIR(9));
    wattr_on(this->main_wind->getWind(), A_REVERSE, NULL);
    wattr_on(this->main_wind->getWind(), A_BOLD, NULL);
    wborder(this->main_wind->getWind(), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wattr_off(this->main_wind->getWind(), A_BOLD, NULL);
    wattr_off(this->main_wind->getWind(), A_REVERSE, NULL);
    wrefresh(this->wind->getWind());
    wrefresh(this->main_wind->getWind());
    refresh();
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
    Vector2 pos(COLS / 2 - (size.x / 2), LINES / 2 - (size.y / 2));
    Vector2 size_main(size.x + 2, size.y + 2);
    Vector2 pos_main(COLS / 2 - ((size.x + 2) / 2), LINES / 2 - ((size.y + 2) / 2));
    if (!this->invalidSize(size.x + 2, size.y + 2, size_main, pos_main))
    {
        if (this->wind)
        {
            clear();
            refresh();
            mvwin(this->main_wind->getWind(), pos_main.y, pos_main.x);
            mvwin(this->wind->getWind(), pos.y, pos.x);
            this->initMainWindow();
        }
        else
        {
            clear();
            refresh();
            this->wind = new Window(size, pos, NULL);
            this->main_wind = new Window(size_main, pos_main, NULL);
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
    AudioComponent  *Aobj;
    UIComponent   *Tobj;

    if (this->valid_size == false)
        return;
    while (!components.empty()) {
        obj = components.top();
        components.pop();
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            if (Gobj->getSpriteText() == ' ')
            {
              wattron(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
              wattr_on(this->wind->getWind(), A_REVERSE, NULL);
              mvwaddch(this->wind->getWind(),
              Gobj->getPos().y, Gobj->getPos().x, Gobj->getSpriteText());
              wattr_off(this->wind->getWind(), A_REVERSE, NULL);
              wattroff(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
            }
            else
            {
              wattron(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
              mvwaddch(this->wind->getWind(),
              Gobj->getPos().y, Gobj->getPos().x, Gobj->getSpriteText());
              wattroff(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
            }
        }
        else if ((Aobj = dynamic_cast<AudioComponent*>(obj)))
          beep();
        else if ((Tobj = dynamic_cast<UIComponent*>(obj)))
        {
          WINDOW *ntext;
          if (Tobj->getPos().x < 0 || Tobj->getPos().y < 0)
            ntext = newwin(Tobj->getSize().y, Tobj->getSize().x, 1, COLS / 2 - (Tobj->getSize().x / 2));
          else
            ntext = newwin(Tobj->getSize().y, Tobj->getSize().x, Tobj->getPos().y, Tobj->getPos().x);
          box(ntext, 0, 0);
          wattr_on(ntext, A_REVERSE, NULL);
          wbkgd(ntext, COLOR_PAIR(Tobj->getColor() + 1));
          wattr_off(ntext, A_REVERSE, NULL);
          mvwprintw(ntext, Tobj->getSize().y / 2, Tobj->getSize().x / 2 - Tobj->getText().length() / 2, "%s", Tobj->getText().c_str());
          wrefresh(ntext);
          refresh();
        }
    }
    wrefresh(this->wind->getWind());
}

void  Ncurses::init(const std::string &name, Vector2 s, std::stack<AComponent*> cache)
{
    (void)name;
    this->size = s;
    initscr();
    cbreak();
    keypad(stdscr, true);
    start_color();
    curs_set(0);
    noecho();
    // halfdelay(1);
    timeout(1);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, -1);
    refresh();
    Vector2 size_main(size.x + 2, size.y + 2);
    Vector2 pos(COLS / 2 - (size.x / 2), LINES / 2 - (size.y / 2));
    Vector2 pos_main(COLS / 2 - ((size.x + 2) / 2), LINES / 2 - ((size.y + 2) / 2));
    if (this->invalidSize(size.x + 2, size.y + 2, size_main, pos_main) == false)
    {
        this->wind = new Window(size, pos, NULL);
        this->main_wind = new Window(size_main, pos_main, NULL);
        keypad(this->wind->getWind(), true);
        this->initMainWindow();
    }
    else
      this->wind = NULL;
    this->display(cache);
}

void    Ncurses::destroy()
 {
     endwin();
 }
