#ifndef LEARNINGMAN_ENVIRONMENT_H
#define LEARNINGMAN_ENVIRONMENT_H
#include "SFML/Graphics.hpp"

class Environment {
public:
    Environment(sf::Vector2f initialPosition1, sf::Vector2f portalPosition1);
    int getReward(sf::Vector2f position, int newHealth);
    int getReward(sf::Vector2f position);
    int getState(sf::Vector2f position);
    void drawStateCases(sf::RenderWindow* window, sf::View view);
    void drawRewardCases(sf::RenderWindow* window, sf::View view);

private:
    void drawCases(sf::RenderWindow* window, sf::View view, float xLag, float yLag, sf::Color color);
    sf::Vector2f portalPosition;
    sf::Vector2f initialPosition;
    float lagXForReward = 4.0;
    float lagYForReward = 3.0;
    float sizeXState = 15.0;
    float sizeYState = 32.0;
    int health = 5;
    int loseHealthReward = -100;
};


#endif //LEARNINGMAN_ENVIRONMENT_H
