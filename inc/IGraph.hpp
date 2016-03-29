/*
** IGraph.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:47:17 2016 Nicolas Constanty
** Last update	Mon Mar 28 22:14:42 2016 Nicolas Constanty
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

# include <stack>
# include <iostream>
# include <AComponent.hpp>

class IGraph {
public:
  virtual int   eventManagment() = 0;
  virtual void  display(std::stack<AComponent*>) = 0;
  virtual void  init(const std::string &name, Vector2<int> size, std::stack<AComponent*>) = 0;
  virtual void  destroy() = 0;
  virtual ~IGraph() {};
};

#endif /* !IGRAPH_HPP_ */
