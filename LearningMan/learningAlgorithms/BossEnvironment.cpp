//
// Created by quent on 21/07/2021.
//

#include "BossEnvironment.h"

BossEnvironment::BossEnvironment(float initialPositionY1){
    lowestX = 3700;
    highestX = 4300;
    initialPositionY = initialPositionY1;
}

BossEnvironment::BossEnvironment(float lowestX1, float highestX1, float initialPositionY1){
    lowestX = lowestX1;
    highestX = highestX1;
    initialPositionY = initialPositionY1;
}

int BossEnvironment::getReward(Controller controller, sf::Sprite boss){
    if(currentHealth == -1){
        currentHealth = controller.character.health;
    }

    bool haveTouch = false;
    if(controller.lastBulletOrientation != 0){
        //if(controller.lastBulletOrientation < 0 && controller.lastBulletOrigin.x > boss.getPosition().x
        if(controller.lastBulletOrientation < 0){
            sf::Sprite bullet = controller.character.bullet;
            float y = bullet.getPosition().y;
            for(float x = controller.lastBulletOrigin.x; x > lowestX; x -= controller.character.bulletSpeed){
                bullet.setPosition(x, y);
                if(bullet.getGlobalBounds().intersects(boss.getGlobalBounds())){
                    haveTouch = true;
                    break;
                }
            }
        }
        else if(controller.lastBulletOrientation > 0){
            sf::Sprite bullet = controller.character.bullet;
            float y = bullet.getPosition().y;
            for(float x = controller.lastBulletOrigin.x; x < highestX; x += controller.character.bulletSpeed){
                bullet.setPosition(x, y);
                if(bullet.getGlobalBounds().intersects(boss.getGlobalBounds())){
                    haveTouch = true;
                    break;
                }
            }
        }
    }
    return (currentHealth - controller.character.health) * lossHealthReward + (haveTouch ? attackBossReward : 0);
}

void BossEnvironment::reset(){
    currentHealth = -1;
}

int BossEnvironment::getState(sf::Vector2f position){
    int availablesXStates = (highestX - lowestX) / sizeXState;
    int xState = (position.x - lowestX) / sizeXState;
    int yState = (initialPositionY - position.y) / sizeYState;
    return (int)(xState + availablesXStates * yState);
}

