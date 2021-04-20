#include "Character.hpp"
#include <iostream>

Character::Character(){

}

void Character::move(int direction) {
    sprite.setScale(direction, 1);
    sprite.move(direction * speed, 0);
}

void Character::shoot(){
    /*
    IntRect rect = sprite.getTextureRect();
    if (clock.getElapsedTime().asSeconds() > 1.0f){
        if (rect.top == 120)
            rect.top = 0;
        else
            rect.top += 30;
        sprite.setTextureRect(rect);
        clock.restart();
    }
     */
    IntRect rect = sprite.getTextureRect();
    rect.width = 70;
    sprite.setTextureRect(rect);
    sprite.setTexture(textureShoot);
}