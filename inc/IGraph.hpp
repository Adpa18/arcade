/*
** IGraph.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:47:17 2016 Nicolas Constanty
** Last update	Tue Mar 08 17:49:28 2016 Nicolas Constanty
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

# include <stack>
# include "Object.hpp"

class IGraph {
public:
  virtual void eventManagment() = 0;
  virtual void refresh(std::stack<Object *>) = 0;
  virtual size_t getKey() const = 0;
};

#endif /* !IGRAPH_HPP_ */
