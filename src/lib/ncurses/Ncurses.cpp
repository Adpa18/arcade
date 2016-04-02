#include <iostream>
#include "Ncurses.hpp"

using namespace ncurses;

Ncurses::Ncurses (void) : size(ArcadeSystem::winWidth, ArcadeSystem::winHeight)
{
  this->valid_size = false;
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
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
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
}

Ncurses::~Ncurses ()
{
    endwin();
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

    key = getch();
    if (key == KEY_RESIZE)
        return (this->resizeTerm());
    if (key == 27) {
        endwin();
    }
    if (this->keyMap[key]) {
        return (this->keyMap[key]);
    }
    return (key);
}

void Ncurses::display(std::stack<AComponent*> components)
{
    AComponent      *obj;
    GameComponent   *Gobj;
    AudioComponent  *Aobj;
    UIComponent     *Uobj;
    HighScoreComponent  *Hobj;

    if (this->valid_size == false)
        return;
    while (!old_component.empty()) {
      wattron(this->wind->getWind(), COLOR_PAIR(AComponent::BLACK + 1));
      wattr_on(this->wind->getWind(), A_REVERSE, NULL);
      mvwaddch(this->wind->getWind(),
      old_component.top().y, old_component.top().x, ' ');
      wattr_off(this->wind->getWind(), A_REVERSE, NULL);
      wattroff(this->wind->getWind(), COLOR_PAIR(AComponent::BLACK + 1));
      old_component.pop();
    }
    while (!old_componentUI.empty()) {
        wclear(old_componentUI.top());
        wrefresh(old_componentUI.top());
        delwin(old_componentUI.top());
        old_componentUI.pop();
    }
    this->i = 0;
    while (!components.empty()) {
        obj = components.top();
        components.pop();
        if ((Gobj = dynamic_cast<GameComponent*>(obj))) {
            this->displayGame(*Gobj);
        } else if ((Aobj = dynamic_cast<AudioComponent*>(obj))) {
            beep();
        } else if ((Uobj = dynamic_cast<UIComponent*>(obj))) {
            this->displayUI(*Uobj);
        } else if ((Hobj = dynamic_cast<HighScoreComponent*>(obj))) {
            this->displayHighScore(Hobj->getComponentsToDisplay());
        }
    }
    wrefresh(this->wind->getWind());
}

void          Ncurses::displayGame(const GameComponent &game)
{
    old_component.push(game.getPos());
    wattron(this->wind->getWind(), COLOR_PAIR(game.getColor() + 1));
    if (game.getSpriteText()[0] == ' ') {
      wattr_on(this->wind->getWind(), A_REVERSE, NULL);
      mvwaddch(this->wind->getWind(),
      game.getPos().y, game.getPos().x, game.getSpriteText()[0]);
      wattr_off(this->wind->getWind(), A_REVERSE, NULL);
    } else {
      mvwaddch(this->wind->getWind(),
      game.getPos().y, game.getPos().x, game.getSpriteText()[0]);
    }
    wattroff(this->wind->getWind(), COLOR_PAIR(game.getColor() + 1));
}

void         Ncurses::displayUI(const UIComponent &ui)
{
    WINDOW  *text;

    if (!ui.getText().length()) {
        return;
    }
    Vector2<double> pos(COLS / 2 - size.x / 2, LINES / 2 - size.y + ui.getPos().y + this->i);
    text = newwin(3, size.x, pos.y, pos.x);
    box(text, 0, 0);
    wattr_on(text, A_REVERSE, NULL);
    wbkgd(text, COLOR_PAIR(ui.getColor() + 1));
    wattr_off(text, A_REVERSE, NULL);
    mvwprintw(text, 1, (size.x - ui.getText().length()) / 2, "%s", ui.getText().c_str());
    wrefresh(text);
    refresh();
    old_componentUI.push(text);
    this->i += 4;
}

void          Ncurses::displayHighScore(UIComponent const * const *uiComponents)
{
    wclear(this->wind->getWind());
    wrefresh(this->wind->getWind());
    for (size_t i = 0; i < HighScoreComponent::componentNb && uiComponents[i] != NULL; i++) {
        displayUI(*uiComponents[i]);
    }
}
