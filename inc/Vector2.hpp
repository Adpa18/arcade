/*
** vector2.hpp for
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:07:00 2016 Nicolas Constanty
** Last update	Tue Mar 15 19:42:58 2016 Adrien WERY
*/

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

# include <cstdlib>

class Vector2 {
public:
    int x;
    int y;
    Vector2 (int x, int y);
    virtual ~Vector2 ();
    Vector2(const Vector2 &obj);
    Vector2 &operator=(const Vector2 &obj);
    bool    operator==(const Vector2 &obj) const;
};

#endif /* !VECTOR2_HPP_ */
