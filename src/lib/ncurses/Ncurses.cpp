/*
** Ncurses.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 23:35:04 2016 Nicolas Constanty
** Last update	Wed Mar 09 20:39:16 2016 Nicolas Constanty
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
  keypad(stdscr, true);
  halfdelay(1);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_MAGENTA);

  wbkgd(stdscr, COLOR_PAIR(1));
  wattr_on(stdscr, A_REVERSE, NULL);
  wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattr_off(stdscr, A_REVERSE, NULL);
  wrefresh(stdscr);
}

Ncurses::~Ncurses ()
{}

int Ncurses::eventManagment()
{
  getch();
  return (0);
}

void Ncurses::display(std::stack<AComponent> *)
{
  // Object2D *obj = static_cast<Object2D *>(objects.top());
  // Vector2 vec = obj->getCoord<Vector2>();
  // std::cout << "x = " << vec.x << " y = " << vec.y << std::endl;
}
