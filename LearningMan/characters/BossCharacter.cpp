#include "BossCharacter.h"

BossCharacter::BossCharacter() : Character() {


}

void BossCharacter::awake(){
    sprite = textureAwake.getCurrentSprite(sprite.getPosition());
}

float BossCharacter::getCorrectScale(int orientation, float scaleX){
    if((orientation == 1 && scaleX < 0) || (orientation == -1 && scaleX > 0)){
        return -scaleX;
    }
    return scaleX;
}

void BossCharacter::setTextureOrientation(int orientation){
    textureAwake.scale.x = getCorrectScale(orientation, textureAwake.scale.x);
    textureAttack1.scale.x = getCorrectScale(orientation, textureAttack1.scale.x);
    projectileAttack1.scale.x = getCorrectScale(orientation, projectileAttack1.scale.x);
    textureAttack2.scale.x = getCorrectScale(orientation, textureAttack2.scale.x);
    projectileAttack2.scale.x = getCorrectScale(orientation, projectileAttack2.scale.x);
    textureAttack3.scale.x = getCorrectScale(orientation, textureAttack3.scale.x);
    projectileAttack3.scale.x = getCorrectScale(orientation, projectileAttack3.scale.x);
}

bool BossCharacter::attack(int i){
    sf::Vector2f position = sprite.getPosition();
    if(i == 1) {
        sprite = textureAttack1.getCurrentSprite(sprite.getPosition());
        if(textureAttack1.currentIt == textureAttack1.size - 1) {
            if(sprite.getScale().x < 0){
                projectiles.push_back(projectileAttack1.toSprite(position + sf::Vector2f(-60, 0)));
            }
            else {
                projectiles.push_back(projectileAttack1.toSprite(position + sf::Vector2f(60, 0)));
            }
            projectilesMovement.push_back(ProjectileMovement::Immobile);
            projectilesClock.push_back(sf::Clock());
            return true;
        }
        return false;
    }
    else if(i == 2) {
        sprite = textureAttack2.getCurrentSprite(position  + sf::Vector2f(0, -0.7));
        if(textureAttack2.currentIt == textureAttack2.size - 1) {
            int numberOfRocks = rand() % 4 + 2;
            for(int j = 0; j < numberOfRocks; j++) {
                int xEcart = rand() % 150 + 50;
                if(rand() % 2 == 0){
                    xEcart = -xEcart;
                }

                projectiles.push_back(projectileAttack2.getCurrentSprite(sf::Vector2f(position.x + xEcart, 400)));
                projectilesMovement.push_back(ProjectileMovement::Down);
                projectilesClock.push_back(sf::Clock());
            }
            return true;
        }
        return false;
    }
    else if(i == 3) {
        sprite = textureAttack3.getCurrentSprite(sprite.getPosition()  + sf::Vector2f(0, -0.5));
        if(textureAttack3.currentIt == textureAttack3.size - 1) {
            if(sprite.getScale().x < 0){
                projectiles.push_back(projectileAttack1.toSprite(position + sf::Vector2f(-60, 0)));
            }
            else {
                projectiles.push_back(projectileAttack3.toSprite(position + sf::Vector2f(60, 0)));
            }
            projectilesMovement.push_back(ProjectileMovement::Immobile);
            projectilesClock.push_back(sf::Clock());
            return true;
        }
        return false;
    }
    return false;
}