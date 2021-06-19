#include "Controller.hpp"
#include <math.h>

Controller::Controller(Character *character1) {
    character = *character1;
}

Action Controller::play(Character ennemi) {
    float scopeVision = 300;
    if(ennemi.sprite.getPosition().x + scopeVision > character.sprite.getPosition().x
       || ennemi.sprite.getPosition().x - scopeVision < character.sprite.getPosition().x) {
        return play();
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
bool Controller::isHealing() {
    return false;
}

Action Controller::play() {
    if(character.health <= 0){
        if(character.dying()) {
            return Action::ToDestroy;
        }
        return Action::None;
    }

    character.velocity.x *= 0.2f;
    bool doingSomething = false;

    if (isGoingRight()) {
        if(character.canMove) {
            character.velocity.x += character.speed;
            character.moving();
        }
        character.sprite.setScale(1, 1);
        doingSomething = true;
    } else if (isGoingLeft()) {
        if(character.canMove) {
            character.velocity.x -= character.speed;
            character.moving();
        }
        character.sprite.setScale(-1, 1);
        doingSomething = true;
    }


    if (isJumping() && character.canJump && character.clockJumpCooldown.getElapsedTime().asMilliseconds() > 300) {
        character.canJump = false;
        character.velocity.y = -sqrtf(2.0f * character.gravity * character.jumpHeight);
        this->sp.playSound("jump.wav");
        character.clockJumpCooldown.restart();
    }


    if (character.sprite.getPosition().y > GRAVITY_POINT + character.gravityDecalage || character.canJump) {
        character.canJump = true;
        character.sprite.setPosition(character.sprite.getPosition().x, GRAVITY_POINT + character.gravityDecalage);
        character.velocity.y = 0;
    } else {
        character.velocity.y += character.gravity;
    }

    if(character.id == "null" ||  character.id == "shotgunner"){
        if(isShooting() && character.canShoot()){
            doingSomething = true;
            character.shoot();
            if(character.sprite.getScale().x == -1){
                bullets.push_back(character.sprite.getPosition() - sf::Vector2f(60,0));
                bulletsOrigin.push_back(character.sprite.getPosition() - sf::Vector2f(60,0));
            }
            else{
                bullets.push_back(character.sprite.getPosition() + sf::Vector2f(60,0));
                bulletsOrigin.push_back(character.sprite.getPosition() + sf::Vector2f(60,0));
            }
            this->sp.playSound("shoot.wav");
            bulletsOrientation.push_back(character.sprite.getScale().x);
            return Action::Shoot;
        }
    }
    else if(character.id == "healer"){
        if(isHealing() && character.canHeal()){
            startHealAnimation = true;
            doingSomething = true;
            character.heal();
            return Action::Heal;
        }
        else if(startHealAnimation){
            if(character.heal()){
                character.launchHeal = true;
                startHealAnimation = false;
            }
            doingSomething = true;
            return Action::Heal;
        }
    }

    if(!doingSomething){
        character.wait();
    }

    character.sprite.move(character.velocity);
    return Action::None;
}