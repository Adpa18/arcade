/*
** AudioComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 09 15:40:56 2016 Nicolas Constanty
** Last update	Mon Mar 28 21:21:57 2016 Nicolas Constanty
*/

#ifndef AUDIOCOMPONENT_HPP_
# define AUDIOCOMPONENT_HPP_

# include <string>
# include "AComponent.hpp"

class AudioComponent : public AComponent {
private:
  char        sound_term;
  std::string sound_2D;
  std::string sound_3D;
public:
  AudioComponent(Vector2<double> const &pos, ComponentColor color,
    char const s_term, std::string const &s_2D, std::string const &s_3D);
  virtual ~AudioComponent();
  char const &getSoundTerm() const;
  std::string const &getSound2D() const;
  std::string const &getSound3D() const;
};

#endif /* !AUDIOCOMPONENT_HPP_ */
