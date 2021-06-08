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

void Character::reset(sf::Vector2f position) {
    health = 5;
    sprite.setPosition(position);
}

void Character::moving(){
    sprite = textureMoving.getCurrentSprite(sprite.getPosition());
}

void Character::shoot(){
    Vector2f scale = sprite.getScale();
    sprite = textureShoot.toSprite(sprite.getPosition());
    sprite.setScale(scale);
}
void Character::heal(){
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
bool Character::canHeal(){
    if(clockBullet.getElapsedTime().asSeconds() > shootCooldown){
        clockBullet.restart();
        return true;
    }
    return false;
}

bool Character::dying() {
    sprite = textureDeath.getCurrentSprite(sprite.getPosition());
    if(textureDeath.currentIt == textureDeath.size - 1)
        return true;
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