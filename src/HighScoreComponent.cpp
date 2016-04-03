//
// Created by gaspar_q on 3/15/16.
//

#include "HighScoreComponent.hpp"
#include "ArcadeSystem.hpp"

const std::string   HighScoreComponent::pseudoPlaceholder("Enter your pseudo");
const std::string   HighScoreComponent::labelHighscores("Highscores");
const Vector2<double>  HighScoreComponent::highscoreDim(15, 20);
const Vector2<double>  HighScoreComponent::highscorePos(7, 5);

static std::string  pseudo(HighScoreComponent::pseudoPlaceholder);

HighScoreComponent::HighScoreComponent(std::string const &gameName, int score) :
    AComponent(HighScoreComponent::highscorePos, AComponent::ComponentColor::WHITE),
    gameName(gameName),
    highScores(gameName + ".arcade"),
    score(score)
{
    const std::vector<const t_highScore *>  scores = highScores.getAllHighScore();

    //Nom du jeu
    components[ComponentsPos::GAMENAME] = new UIComponent(Vector2<double>(0, 0), AComponent::ComponentColor::WHITE, Vector2<double>(0, 0), "");
    //Score
    components[HighScoreComponent::ComponentsPos::SCORE] = new UIComponent(Vector2<double>(0, 0), AComponent::ComponentColor::WHITE, Vector2<double>(0, 0), "");
    //Enter you pseudo
    components[ComponentsPos::PSEUDO] = new UIComponent(
        Vector2<double>(ArcadeSystem::winWidth / 2, 3), AComponent::ComponentColor::YELLOW,
        Vector2<double>(0, 0), HighScoreComponent::pseudoPlaceholder);
    //Highscores label
    components[ComponentsPos::LABEL] = new UIComponent(
        Vector2<double>(ArcadeSystem::winWidth / 2, 5), AComponent::ComponentColor::WHITE,
        Vector2<double>(0, 0), HighScoreComponent::labelHighscores);
    // All scores
    for (size_t i = 0, len = scores.size(); i < 10; i++) {
        if (i < len) {
            components[i + 3] = new UIComponent(
                Vector2<double>(ArcadeSystem::winWidth / 2, (i * 2) + 7), AComponent::ComponentColor::WHITE,
                Vector2<double>(0, 0), scores[i]->getName() + std::string(" ") + std::to_string(scores[i]->getScore()));
        } else {
            components[i + 3] = NULL;
        }
    }
    components[13] = NULL;
}

HighScoreComponent::~HighScoreComponent()
{
    for (size_t i = 0; i < HighScoreComponent::componentNb && components[i] != NULL; ++i) {
        delete(components[i]);
    }
}

void HighScoreComponent::UpdatePseudo(const int key)
{
    if (key == ArcadeSystem::Backspace)
    {
        if (!pseudo.empty() && pseudo != HighScoreComponent::pseudoPlaceholder)
            pseudo = pseudo.substr(0, pseudo.length() - 1);
    }
    else if (key >= ' ' && key <= '~' && pseudo.length() < 20)
    {
        if (pseudo == HighScoreComponent::pseudoPlaceholder)
            pseudo.clear();
        pseudo.push_back(static_cast<char>(key));
    }

    if (pseudo.empty())
        pseudo = HighScoreComponent::pseudoPlaceholder;
    delete(components[HighScoreComponent::ComponentsPos::PSEUDO]);
    components[HighScoreComponent::ComponentsPos::PSEUDO] = new UIComponent(
        Vector2<double>(ArcadeSystem::winWidth / 2, 3), AComponent::ComponentColor::WHITE,
        Vector2<double>(0, 0), pseudo);
}

UIComponent const * const *HighScoreComponent::getComponentsToDisplay() const
{
    return components;
}

bool    HighScoreComponent::submit()
{
    if (pseudo.empty() || pseudo == HighScoreComponent::pseudoPlaceholder) {
        return true;
    }
    highScores.setHighScore(new t_highScore(score, pseudo));
    highScores.flush();
    pseudo = HighScoreComponent::pseudoPlaceholder;
    return true;
}
