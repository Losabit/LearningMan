#include "PredefineController.hpp"
#include <math.h>

PredefineController::PredefineController(Character* character1) : Controller(character1) {

}

PredefineController::PredefineController(Character* character1,  std::vector<int> actions1) : Controller(character1) {
    for(int i = 0; i < actions1.size(); i++){
        actions.push_back(actions1.at(i));
    }
}

bool PredefineController::isGoingRight(){
    if(actualActionIndice < actions.size()) {
        if (static_cast<PredefineAction>(actions.at(actualActionIndice)) == PredefineAction::RightAction) {
            actualActionIndice++;
            return true;
        }
    }
    return false;
}

bool PredefineController::isGoingLeft() {
    if(actualActionIndice < actions.size()) {
        if (static_cast<PredefineAction>(actions[actualActionIndice]) == PredefineAction::LeftAction) {
            actualActionIndice++;
            return true;
        }
    }
    return false;
}

bool PredefineController::isJumping() {
    if(actualActionIndice < actions.size()) {
        if (static_cast<PredefineAction>(actions[actualActionIndice]) == PredefineAction::JumpAction) {
            actualActionIndice++;
            return true;
        }
    }
    return false;
}

bool PredefineController::isShooting() {
    if(actualActionIndice < actions.size()) {
        if (static_cast<PredefineAction>(actions[actualActionIndice]) == PredefineAction::ShootAction) {
            actualActionIndice++;
            return true;
        }
    }
    return false;
}

Action PredefineController::play(PredefineAction action){
    if(character.health <= 0){
        if(character.dying()) {
            return Action::ToDestroy;
        }
        return Action::None;
    }

    character.velocity.x *= 0.2f;
    bool doingSomething = false;

    if (action == PredefineAction::RightAction) {
        if(character.canMove) {
            character.velocity.x += character.speed;
            character.moving();
        }
        character.sprite.setScale(1, 1);
        doingSomething = true;
    } else if (action == PredefineAction::LeftAction) {
        if(character.canMove) {
            character.velocity.x -= character.speed;
            character.moving();
        }
        character.sprite.setScale(-1, 1);
        doingSomething = true;
    }


    if (action == PredefineAction::JumpAction && character.canJump && character.clockJumpCooldown.getElapsedTime().asMilliseconds() > 300) {
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
        if(action == PredefineAction::ShootAction && character.canShoot()){
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

    if(!doingSomething){
        character.wait();
    }

    character.sprite.move(character.velocity);
    return Action::None;
}
