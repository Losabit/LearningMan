#include "BossController.h"

BossController::BossController(BossCharacter* character1) {
    character = *character1;
    character.sprite.setPosition(character.sprite.getPosition().x, GRAVITY_POINT + character.gravityDecalage);
}

Action BossController::play(Character ennemi){
    if(ennemi.sprite.getPosition().x - character.sprite.getPosition().x > 0 && character.sprite.getScale().x != 1){
        character.sprite.setScale(1, 1);
        character.setTextureOrientation(1);
    }
    else if(ennemi.sprite.getPosition().x - character.sprite.getPosition().x < 0 && character.sprite.getScale().x != -1){
        character.sprite.setScale(-1, 1);
        character.setTextureOrientation(-1);
    }
    return play();
}

Action BossController::play() {
    bool doingSomething = false;
    if(character.health <= 0){
        if(character.sprite.getPosition().y < GRAVITY_POINT + character.gravityDecalage){
            character.sprite.move(0, 5);
            if(character.sprite.getPosition().y > GRAVITY_POINT + character.gravityDecalage){
                this->sp.playSound("rock.wav");
                character.sprite.setPosition(character.sprite.getPosition().x, GRAVITY_POINT + character.gravityDecalage);
            }
        }
        if(character.dying()) {
            return Action::ToDestroy;
        }
        return Action::None;
    }

    if(lastAttackClock.getElapsedTime().asSeconds() > 1.5) {
        if (attackIndice == 0) {
            this->sp.playSound("attack.wav");
            attackIndice = rand() % 3 + 1;
        }
        if (character.attack(attackIndice)) {
            if(attackIndice == 1 || attackIndice == 3){
                this->sp.playSound("laser.wav");
            }
            attackIndice = 0;
            lastAttackClock.restart();
        }
        doingSomething = true;
    }

    if(!doingSomething) {
        character.wait();
        if(character.sprite.getPosition().y < GRAVITY_POINT + character.gravityDecalage){
            character.sprite.move(0, 5);
            if(character.sprite.getPosition().y > GRAVITY_POINT + character.gravityDecalage){
                character.sprite.setPosition(character.sprite.getPosition().x, GRAVITY_POINT + character.gravityDecalage);
            }
        }
    }

    return Action::None;
}

void BossController::setPlayerPosition(Vector2f position){
    playerPosition = position;
}