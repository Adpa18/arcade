/*
** ScoreComponent.cpp for cpp_arcade
**
** Made by	Nicolas Constanty
** Login	consta_n
**
** Started on	Wed Mar 16 21:34:17 2016 Nicolas Constanty
** Last update	Mon Mar 28 11:06:35 2016 Adrien WERY
*/

#include "ScoreComponent.hpp"

ScoreComponent::ScoreComponent(const std::string &game) : game(game)
{
    std::fstream file;

    file.open("./assets/scores/" + game, std::fstream::out | std::fstream::binary);
    if (file.is_open()) {
        file.read((char*)&this->header, sizeof(t_header));
        for (int i = 0; i < this->header.nbrHighScore; i++) {
            file.read((char*)&this->hightScore[i], sizeof(t_highScore));
        }
        file.close();
    } else {
        writeScore();
    }
    this->text = new UIComponent(Vector2(-1, -1), Vector2(50, 5), WHITE, "", "frenchy", 60);
    this->score = 0;
}

ScoreComponent::~ScoreComponent()
{

}

size_t    ScoreComponent::getScore() const
{
    return (this->score);
}

UIComponent    *ScoreComponent::getScoreUI()
{
    return (this->text);
}


void      ScoreComponent::setScore(size_t score)
{
    this->score = score;
}

void    ScoreComponent::writeScore()
{
    std::fstream file;
    t_highScore  hScore;

    strcpy(hScore.name, "Toto");
    hScore.score = this->score;
    this->hightScore.push_back(hScore);
    file.open("./assets/scores/" + this->game, std::fstream::in | std::fstream::binary);
    if (file.is_open()) {
        file.write((char*)&this->header, sizeof(t_header));
        for (int i = 0; i < 10; i++) {
            file.write((char*)&this->hightScore[i], sizeof(t_highScore));
        }
    } else {
        std::cerr << "Cannot save score" << std::endl;
    }
    this->score = 0;
    this->text->setText("Score : 0");
}
