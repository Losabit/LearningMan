#include "Character.hpp"

Character::Character(){

}

Character::Character(Sprite sprite1){
    sprite = sprite1;
}

void Character::move(int direction) {
    sprite.setScale(direction, 1);
    sprite.move(direction * speed, 0);
}