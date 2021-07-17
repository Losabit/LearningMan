#include "Environment.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Environment::Environment(sf::Vector2f initialPosition1){
    initialPosition = initialPosition1;
}

int Environment::getReward(sf::Vector2f position){
    //std::cout << "reward " << (int)((position.x - initialPosition.x) / lagForReward) << std::endl;
    return (int)((position.x - initialPosition.x) / lagForReward);
}

int Environment::getState(sf::Vector2f position){
    return (int)((position.x - initialPosition.x) / lagForReward);
}