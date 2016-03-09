/*
** Arcade.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 18:28:59 2016 Nicolas Constanty
** Last update	Wed Mar 09 03:57:32 2016 Nicolas Constanty
*/

#include <iostream>
#include "Arcade.hpp"

int	main()
{
  //Load libx
  void *mysograph = dlopen("./lib/lib_arcade_ncurses.so", RTLD_LAZY);
  if (!mysograph)
  {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return 1;
  }
  //reset error;
  dlerror();
  void *mysogame = dlopen("./games/lib_arcade_snake.so", RTLD_NOW);
  if (!mysograph)
  {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return 1;
  }
  const char *game_name = "_Z8loadGamePv";
  typedef IGame *(*fptr)(void *ptr);
  fptr load_game = (IGame *(*)(void *ptr))(dlsym(mysogame, game_name));
  const char *dlsym_error = dlerror();
  if (dlsym_error)
  {
    std::cerr << "Cannot load symbol '" << game_name << "': " << dlsym_error << '\n';
    dlclose(mysograph);
    dlclose(mysogame);
    return 1;
  }
  IGame *game = (IGame *)load_game(mysograph);
  game->compute();
  dlclose(mysograph);
  dlclose(mysogame);
  return (0);
}
