#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

# include <stack>
# include <iostream>
# include <AComponent.hpp>
# include "ArcadeSystem.hpp"

class IGraph {
public:
  virtual       ~IGraph() {};
  virtual int   eventManagment() = 0;
  virtual void  display(std::stack<AComponent*>) = 0;
  virtual void  init(const std::string &name, Vector2<double> size, std::stack<AComponent*>) = 0;
  virtual void  destroy() = 0;
};

#endif /* !IGRAPH_HPP_ */
