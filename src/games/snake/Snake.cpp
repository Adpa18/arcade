/*
** Snake.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 00:40:10 2016 Nicolas Constanty
** Last update	Wed Mar 09 05:06:20 2016 Nicolas Constanty
*/

#include "Snake.hpp"

Snake::Snake (void *ptr)
{
  std::cout << "StartInit => Snake" << std::endl;
  this->lptr = ptr;
  const char *lib_name = "_Z7loadLibv";
  typedef IGraph *(*fptr)();
  fptr load_lib = (IGraph *(*)())(dlsym(this->lptr, lib_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
  {
    std::cerr << "Cannot load symbol '" << lib_name << "': " << dlsym_error << '\n';
  }
  else
  {
    this->graph = (IGraph *)load_lib();
  }
  std::cout << "EndInit => Snake" << std::endl;
}

Snake::~Snake ()
{}

void Snake::compute()
{
  graph->getKey();
}
