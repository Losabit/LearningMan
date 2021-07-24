#include "PredefineController.hpp"
#include <math.h>

PredefineController::PredefineController(Character* character1) : Controller(character1) {
    SoundPlayer soundPlayer;
    this->sp = soundPlayer;
}

PredefineController::PredefineController(Character* character1,  std::vector<int> actions1) : Controller(character1) {
    for(int i = 0; i < actions1.size(); i++){
        actions.push_back(actions1.at(i));
    }
}

PredefineAction PredefineController::getActionFromInputs() {
    if(Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::D)){
        return PredefineAction::JumpRightAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::Q)){
        return PredefineAction::JumpLeftAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q) && Keyboard::isKeyPressed(Keyboard::Space)){
        return PredefineAction::ShootLeftAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::Space)){
        return PredefineAction::ShootRightAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Z)){
        return PredefineAction::JumpAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::D)){
        return PredefineAction::RightAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q)){
        return PredefineAction::LeftAction;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Space)){
        return PredefineAction::ShootAction;
    }
    return PredefineAction::WaitAction;
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
    lastBulletOrigin = Vector2f(0,0);
    lastBulletOrientation = 0;

    if(character.health <= 0){
        if(character.dying()) {
            return Action::ToDestroy;
        }
        return Action::None;
    }

    character.velocity.x *= 0.2f;
    bool doingSomething = false;

    if (action == PredefineAction::RightAction || action == PredefineAction::JumpRightAction
    || action == PredefineAction::ShootRightAction) {
        if(character.canMove) {
            character.velocity.x += character.speed;
            character.moving();
        }
        character.sprite.setScale(1, 1);
        doingSomething = true;
    } else if (action == PredefineAction::LeftAction || action == PredefineAction::JumpLeftAction
    || action == PredefineAction::ShootLeftAction) {
        if(character.canMove) {
            character.velocity.x -= character.speed;
            character.moving();
        }
        character.sprite.setScale(-1, 1);
        doingSomething = true;
    }


    if ((action == PredefineAction::JumpAction || action == PredefineAction::JumpRightAction || action == PredefineAction::JumpLeftAction) && character.canJump && character.clockJumpCooldown.getElapsedTime().asMilliseconds() > 300) {
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


    if((action == PredefineAction::ShootAction || action == PredefineAction::ShootLeftAction || action == PredefineAction::ShootRightAction)
    && character.canShoot()){
        doingSomething = true;
        character.shoot();
        if(character.sprite.getScale().x == -1){
            bullets.push_back(character.sprite.getPosition() - sf::Vector2f(60,0));
            bulletsOrigin.push_back(character.sprite.getPosition() - sf::Vector2f(60,0));
            lastBulletOrigin = character.sprite.getPosition() - sf::Vector2f(60,0);
        }
        else{
            bullets.push_back(character.sprite.getPosition() + sf::Vector2f(60,0));
            bulletsOrigin.push_back(character.sprite.getPosition() + sf::Vector2f(60,0));
            lastBulletOrigin = character.sprite.getPosition() + sf::Vector2f(60,0);
        }
        this->sp.playSound("shoot.wav");
        bulletsOrientation.push_back(character.sprite.getScale().x);
        lastBulletOrientation = character.sprite.getScale().x;
        return Action::Shoot;
    }


    if(!doingSomething){
        character.wait();
    }

    character.sprite.move(character.velocity);
    return Action::None;
}

std::vector<int> PredefineController::availableActions(){
    std::vector<int> actionsAvailables;
    actionsAvailables.push_back(static_cast<int>(PredefineAction::LeftAction));
    actionsAvailables.push_back(static_cast<int>(PredefineAction::RightAction));

    if(character.canJump && character.clockJumpCooldown.getElapsedTime().asMilliseconds() > 300){
        actionsAvailables.push_back(static_cast<int>(PredefineAction::JumpAction));
        actionsAvailables.push_back(static_cast<int>(PredefineAction::JumpLeftAction));
        actionsAvailables.push_back(static_cast<int>(PredefineAction::JumpRightAction));
    }
    if(character.canShootWithoutReset()){
        actionsAvailables.push_back(static_cast<int>(PredefineAction::ShootLeftAction));
        actionsAvailables.push_back(static_cast<int>(PredefineAction::ShootRightAction));
    }
    return actionsAvailables;
}