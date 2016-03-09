/*
** IGraph.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:47:17 2016 Nicolas Constanty
** Last update	Wed Mar 09 19:20:10 2016 Nicolas Constanty
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

# include <cstdlib>
# include <stack>
# include <AComponent.hpp>

class IGraph {
public:
  virtual void eventManagment() = 0;
  virtual void display(std::stack<AComponent> *) = 0;
  virtual size_t getKey() const = 0;
};

#endif /* !IGRAPH_HPP_ */
