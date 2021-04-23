#include "Character.hpp"
#include "../define.hpp"
#include <iostream>

Character::Character(){

}

void Character::move(int direction) {
    if(clockBullet.getElapsedTime().asSeconds() > TIME_SHOOT_TO_IDLE && sprite.getTexture() != &textureIdle.texture){
        IntRect rect = sprite.getTextureRect();
        rect.width = 40;
        sprite.setTextureRect(rect);
        sprite.setTexture(textureIdle.texture);
    }
    sprite.setScale(direction, 1);
    sprite.move(direction * speed, 0);
}

void Character::shoot(){
    sprite.setTextureRect(textureShoot.rect);
    sprite.setTexture(textureShoot.texture);
}

bool Character::canShoot(){
    if(clockBullet.getElapsedTime().asSeconds() > shootCooldown){
        clockBullet.restart();
        return true;
    }
    return false;
}

void Character::wait() {
    if(clockBullet.getElapsedTime().asSeconds() > TIME_SHOOT_TO_IDLE && sprite.getTexture() != &textureIdle.texture){
        IntRect rect = sprite.getTextureRect();
        rect.width = 40;
        sprite.setTextureRect(rect);
        sprite.setTexture(textureIdle.texture);
    }
}

bool Character::takeDamage(int damage) {
    health -= damage;
    if(health <= 0){
        return false;
    }
    return true;
}