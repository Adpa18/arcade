#include <iostream>
#include "Ncurses.hpp"

using namespace ncurses;

Ncurses::Ncurses (void) : size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
{
  this->is_init = false;
  this->is_destroy = false;
  this->valid_size = false;
}

Ncurses::~Ncurses ()
{
  if (this->is_destroy == false)
    this->destroy();
}

void	Ncurses::initMainWindow()
{
    // wbkgd(this->main_wind->getWind(), COLOR_PAIR(9));
    // wattr_on(this->main_wind->getWind(), A_REVERSE, NULL);
    // wattr_on(this->main_wind->getWind(), A_BOLD, NULL);
    // wborder(this->main_wind->getWind(), ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    // wattr_off(this->main_wind->getWind(), A_BOLD, NULL);
    // wattr_off(this->main_wind->getWind(), A_REVERSE, NULL);
    wrefresh(this->wind->getWind());
    // wrefresh(this->main_wind->getWind());
    refresh();
}

bool	Ncurses::invalidSize(Vector2<double> const &size, Vector2<double> const &pos)
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
        mvprintw(LINES / 2 + 1, COLS / 2 - 12, "Required size : %d x %d", size.x, size.y);
        return (true);
    }
    this->valid_size = true;
    return (false);
}

int	Ncurses::resizeTerm()
{
    Vector2<double> pos(COLS / 2 - (size.x / 2), LINES / 2 - (size.y / 2));
    if (!this->invalidSize(size, pos))
    {
        if (this->wind)
        {
            clear();
            refresh();
            // mvwin(this->main_wind->getWind(), pos_main.y, pos_main.x);
            mvwin(this->wind->getWind(), pos.y, pos.x);
            this->initMainWindow();
        }
        else
        {
            clear();
            refresh();
            // this->main_wind = new Window(size_main, pos_main, NULL);
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

    if (is_init == false)
      this->initc(Vector2<double>(50, 30));
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
    UIComponent     *Tobj;

    if (this->valid_size == false)
        return;
    while (!components.empty()) {
        obj = components.top();
        components.pop();
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            if (Gobj->getSpriteText()[0] == ' ')
            {
              wattron(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
              wattr_on(this->wind->getWind(), A_REVERSE, NULL);
              mvwaddch(this->wind->getWind(),
              Gobj->getPos().y, Gobj->getPos().x, Gobj->getSpriteText()[0]);
              wattr_off(this->wind->getWind(), A_REVERSE, NULL);
              wattroff(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
            }
            else
            {
              wattron(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
              mvwaddch(this->wind->getWind(),
              Gobj->getPos().y, Gobj->getPos().x, Gobj->getSpriteText()[0]);
              wattroff(this->wind->getWind(), COLOR_PAIR(Gobj->getColor() + 1));
            }
        }
        else if ((Aobj = dynamic_cast<AudioComponent*>(obj)))
          beep();
        else if ((Tobj = dynamic_cast<UIComponent*>(obj)))
        {
          WINDOW *ntext;
          if (Tobj->getPos().x < 0 || Tobj->getPos().y < 0)
            ntext = newwin(Tobj->getDim().y, Tobj->getDim().x, 1, COLS / 2 - (Tobj->getDim().x / 2));
          else
          {
            ntext = newwin(Tobj->getDim().y, Tobj->getDim().x, Tobj->getPos().y, Tobj->getPos().x);
            // if (!ntext)
              // perror("");
          }
          box(ntext, 0, 0);
          wattr_on(ntext, A_REVERSE, NULL);
          wbkgd(ntext, COLOR_PAIR(Tobj->getColor() + 1));
          wattr_off(ntext, A_REVERSE, NULL);
          mvwprintw(ntext, Tobj->getDim().y / 2, Tobj->getDim().x / 2 - Tobj->getText().length() / 2,
           "%s", Tobj->getText().c_str());
          wrefresh(ntext);
          refresh();
        }
    }
    wrefresh(this->wind->getWind());
}

void  Ncurses::init(const std::string &name, Vector2<double> s, std::stack<AComponent*> cache)
{
    (void)name;
    this->is_init = true;
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
    Vector2<double> pos(COLS / 2 - (size.x / 2), LINES / 2 - (size.y / 2));
    this->wind = NULL;
    if (this->invalidSize(size, pos) == false)
    {
        this->wind = new Window(size, pos, NULL);
        // this->main_wind = new Window(size_main, pos_main, NULL);
        keypad(this->wind->getWind(), true);
        this->initMainWindow();
    }
    else
      this->wind = NULL;
    this->display(cache);
}

void  Ncurses::initc(Vector2<double> s)
{
    this->size = s;
    this->is_init = true;
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
    this->wind = NULL;
    Vector2<double> pos(COLS / 2 - (size.x / 2), LINES / 2 - (size.y / 2));
    if (this->invalidSize(size, pos) == false)
    {
        this->wind = new Window(size, pos, NULL);
        // this->main_wind = new Window(size_main, pos_main, NULL);
        keypad(this->wind->getWind(), true);
        this->initMainWindow();
    }
    else
      this->wind = NULL;
}

void    Ncurses::destroy()
 {
    this->is_destroy = true;
    endwin();
 }
