/*
** IGraph.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:47:17 2016 Nicolas Constanty
** Last update	Wed Mar 16 07:19:48 2016 Nicolas Constanty
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
  virtual void  init(const std::string &name, Vector2 size, std::stack<AComponent*>) = 0;
};

#endif /* !IGRAPH_HPP_ */
