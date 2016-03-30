/*
** ScoreComponent.hpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:32:30 2016 Nicolas Constanty
** Last update	Tue Mar 29 21:29:22 2016 Nicolas Constanty
*/

#ifndef SCORECOMPONENT_HPP_
# define SCORECOMPONENT_HPP_

# include <string>
# include <iostream>
# include <fstream>
# include <vector>
# include <cstring>
# include "UIAdvanceComponent.hpp"

typedef     struct s_header {
    int     magicNbr;
    int     headerSize;
    int     fileSize;
    int     nbrHighScore;
}           t_header;

typedef             struct s_highScore {
    char            name[20];
    unsigned int    score;
}                   t_highScore;

class ScoreComponent {
private:
    std::string game;
    size_t      score;
    UIAdvanceComponent *text;
    t_header    header;
    std::vector<t_highScore> hightScore;
public:
  ScoreComponent(const std::string &game);
  virtual ~ScoreComponent();
  size_t    getScore() const;
  UIAdvanceComponent    *getScoreUI();
  void      setScore(size_t score);
  void      writeScore();
};

#endif /* !SCORECOMPONENT_HPP_ */