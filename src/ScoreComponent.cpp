#include "ScoreComponent.hpp"

ScoreComponent::ScoreComponent(const std::string &game) : game(game)
{
    std::fstream file;

    file.open("./assets/scores/" + game, std::fstream::out | std::fstream::binary);
    // if (file.is_open()) {
    //     file.read((char*)&this->header, sizeof(t_header));
    //     for (int i = 0; i < this->header.nbrHighScore; i++) {
    //         file.read((char*)&this->hightScore[i], sizeof(t_highScore));
    //     }
    //     file.close();
    // } else {
    //     writeScore();
    // }
    this->text = new UIAdvanceComponent(Vector2<double>(-1, -1), Vector2<double>(50, 5), AComponent::WHITE, "", "frenchy", 60);
    this->score = 0;
}

ScoreComponent::~ScoreComponent()
{

}

size_t    ScoreComponent::getScore() const
{
    return (this->score);
}

UIAdvanceComponent    *ScoreComponent::getScoreUI()
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
