#ifndef LEARNINGMAN_ENVIRONMENT_H
#define LEARNINGMAN_ENVIRONMENT_H
#include "SFML/Graphics.hpp"

class Environment {
public:
    Environment(sf::Vector2f initialPosition1);
    int getReward(sf::Vector2f position);
    int getState(sf::Vector2f position);

private:
    sf::Vector2f initialPosition;
    float lagForReward = 5.0;
};


#endif //LEARNINGMAN_ENVIRONMENT_H
