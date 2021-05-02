#include "Controller.hpp"
#include <math.h>

Controller::Controller(Character *character1) {
    character = *character1;
}

Action Controller::play(Character ennemi) {
    float scopeVision = 300;
    if(ennemi.sprite.getPosition().x + scopeVision > character.sprite.getPosition().x
       && ennemi.sprite.getPosition().x - scopeVision < character.sprite.getPosition().x) {
        play();
    }
    else{
        character.wait();
    }
    return Action::None;
}

bool Controller::isGoingRight() {
    return false;
}

bool Controller::isGoingLeft() {
    return false;
}

bool Controller::isJumping() {
    return false;
}

bool Controller::isShooting() {
    return false;
}

Action Controller::play() {
    character.velocity.x *= 0.2f;
    bool doingSomething = false;
    if(isGoingRight()){
        character.velocity.x += character.speed;
        character.sprite.setScale(1, 1);
        doingSomething = true;
    }
    else if(isGoingLeft()){
        character.velocity.x -= character.speed;
        character.sprite.setScale(-1, 1);
        doingSomething = true;
    }

    //std::cout << character.sprite.getPosition().y << std::endl;
    if (isJumping() && character.canJump) {
        jumpPosition = character.sprite.getPosition();
        character.canJump = false;
        character.velocity.y = -sqrtf(2.0f * character.gravity * character.jumpHeight);
        this->sp.playSound("jump.wav");
    }

    if (character.sprite.getPosition().y >= GRAVITY_POINT) {
        character.canJump = true;
        character.sprite.setPosition(character.sprite.getPosition().x, GRAVITY_POINT);
    } else {
        character.velocity.y += character.gravity;
    }

    if(isShooting()){
        if(character.canShoot()){
            doingSomething = true;
            character.shoot();
            if(character.sprite.getScale().x == -1){
                bullets.push_back(character.sprite.getPosition() - sf::Vector2f(100,0));
            }
            else{
                bullets.push_back(character.sprite.getPosition());
            }
            this->sp.playSound("shoot.wav");
            bulletsOrientation.push_back(character.sprite.getScale().x);
            return Action::Shoot;
        }
    }

    if(!doingSomething){
        character.wait();
    }

    character.sprite.move(character.velocity);

    return Action::None;
}