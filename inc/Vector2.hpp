/*
** vector2.hpp for
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Tue Mar 08 17:07:00 2016 Nicolas Constanty
** Last update	Mon Mar 28 22:00:50 2016 Nicolas Constanty
*/

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

# include <cstdlib>

template <class T>
class Vector2 {
public:
    T x;
    T y;

    Vector2(T x, T y)
    {
      this->x = x;
      this->y = y;
    }


    Vector2(const Vector2<T> &obj)
    {
      *this = obj;
    }
    
    ~Vector2()
    {}

    Vector2<T> &operator=(const Vector2<T> &vec)
    {
      this->x = vec.x;
      this->y = vec.y;
      return *this;
    }

    bool    operator==(const Vector2<T> &vec) const
    {
        return (this->x == vec.x && this->y == vec.y);
    }

};

#endif /* !VECTOR2_HPP_ */
