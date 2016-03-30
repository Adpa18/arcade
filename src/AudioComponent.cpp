#include "AudioComponent.hpp"

AudioComponent::AudioComponent(Vector2<double> const &pos, ComponentColor color,
  char const s_term, std::string const &s_2D, std::string const &s_3D)
 : AComponent(pos, color)
{
  this->sound_term = s_term;
  this->sound_2D = s_2D;
  this->sound_3D = s_3D;
}

AudioComponent::~AudioComponent()
{}

char const &AudioComponent::getSoundTerm() const
{
  return (this->sound_term);
}

std::string const &AudioComponent::getSound2D() const
{
  return (this->sound_2D);
}

std::string const &AudioComponent::getSound3D() const
{
  return (this->sound_3D);
}
