#include "Character.hpp"
#include "../define.hpp"
#include <iostream>

Character::Character(){

}

void Character::move(int direction) {
    if(clockBullet.getElapsedTime().asSeconds() > TIME_SHOOT_TO_IDLE && sprite.getTexture() != &textureIdle.texture){
        sprite.setTextureRect(textureIdle.rect);
        sprite.setTexture(textureIdle.texture);
    }
    sprite.setScale(direction, 1);
    sprite.move(direction * speed, 0);
}

void Character::shoot(){
    Vector2f scale = sprite.getScale();
    sprite = textureShoot.toSprite(sprite.getPosition());
    sprite.setScale(scale);
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
        sprite.setTextureRect(textureIdle.rect);
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