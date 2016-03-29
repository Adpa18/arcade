/*
** IGraph.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:47:17 2016 Nicolas Constanty
** Last update	Tue Mar 29 16:43:48 2016 Nicolas Constanty
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

# include <stack>
# include <iostream>
# include <AComponent.hpp>

class IGraph {
public:
  virtual       ~IGraph() {};
  virtual int   eventManagment() = 0;
  virtual void  display(std::stack<AComponent*>) = 0;
  virtual void  init(const std::string &name, Vector2<double> size, std::stack<AComponent*>) = 0;
  virtual void  destroy() = 0;
};

#endif /* !IGRAPH_HPP_ */
