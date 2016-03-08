/*
** Object2D.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:50:09 2016 Nicolas Constanty
** Last update	Tue Mar 08 18:06:19 2016 Nicolas Constanty
*/

#ifndef OBJECT2D_HPP_
#define OBJECT2D_HPP_

# include <string>
# include "Object.hpp"

class Object2D : public Object {
private:
  std::string fileName;
public:
  Object2D(std::string const &newFileName, Vector2 const &coord,
     Vector2 const &dim);
  virtual ~Object2D();
  std::string const &getFIleName() const;
};

#endif /* !OBJECT2D_HPP_ */
