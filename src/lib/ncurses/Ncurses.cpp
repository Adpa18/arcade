/*
** Ncurses.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 23:35:04 2016 Nicolas Constanty
** Last update	Wed Mar 09 06:54:49 2016 Nicolas Constanty
*/

#include <iostream>
#include "Ncurses.hpp"

using namespace ncurses;

Ncurses::Ncurses (void)
{
  std::cout << "StartInit => Lib Ncurses" << std::endl;

  initscr();
  start_color();
  curs_set(0);
  noecho();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_MAGENTA);

  wbkgd(stdscr, COLOR_PAIR(1));
  wattr_on(stdscr, A_REVERSE, NULL);
  wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattr_off(stdscr, A_REVERSE, NULL);

  Window *menu = NULL;
  Vector2 *size;
  Vector2 *pos;

  int key;
  while ((key = getch()) != 27) {
      if (key == KEY_RESIZE) {
          clear();
          wattr_on(stdscr, A_REVERSE, NULL);
          wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
          wattr_off(stdscr, A_REVERSE, NULL);
          if (menu && menu->getWind())
          {
            pos = new Vector2(LINES / 4, COLS / 4);
            size = new Vector2(LINES / 2, COLS / 2);
            menu->setWind(*size, *pos, NULL);
          }
      }
      if (key == 32)
      {
        if (menu && menu->getWind())
          menu->close();
        else
        {
          pos = new Vector2(LINES / 4, COLS / 4);
          size = new Vector2(LINES / 2, COLS / 2);
          menu = new Window(*size, *pos, NULL);
        }
      }
  }

  // Vector2 pos(3, 3);
  // Vector2 size(10, 10);
  // Window *wind = new Window(size, pos, NULL);
  //
  // wind->getPos();

  std::cout << "EndInit => Lib Ncurses" << std::endl;
  getch();
}

Ncurses::~Ncurses ()
{}

void Ncurses::eventManagment()
{

}

void Ncurses::display(std::stack<Object *> objects)
{
  Object2D *obj = static_cast<Object2D *>(objects.top());
  Vector2 vec = obj->getCoord<Vector2>();
  std::cout << "x = " << vec.x << " y = " << vec.y << std::endl;
}

size_t Ncurses::getKey() const
{
  return (0);
}
