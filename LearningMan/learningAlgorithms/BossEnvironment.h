//
// Created by quent on 21/07/2021.
//

#ifndef LEARNINGMAN_BOSSENVIRONMENT_H
#define LEARNINGMAN_BOSSENVIRONMENT_H
#include <SFML/Graphics.hpp>
#include "../controllers/Controller.hpp"

class BossEnvironment {
public:
    BossEnvironment(float initialPositionY1);
    BossEnvironment(float lowestX1, float highestX1, float initialPositionY1);
    int getReward(Controller controller, sf::Sprite boss);
    int getState(sf::Vector2f position);
    int getBossState(sf::Vector2f position, sf::Vector2f bossPosition);
    void reset();

private:
    float lowestX;
    float highestX;
    float initialPositionY;
    float sizeXState = 15.0;
    float sizeYState = 32.0;
    int attackBossReward = 15;
    int lossHealthReward = -10;
    int currentHealth = -1;
};


#endif //LEARNINGMAN_BOSSENVIRONMENT_H
