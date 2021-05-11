#include "IAController.hpp"


IAController::IAController(Character* character1) : Controller(character1) {
}


bool IAController::isGoingRight(){
    if(character.sprite.getPosition().x + scope > playerPosition.x && !(character.sprite.getPosition().x + (scope / 2) > playerPosition.x)) {
        return true;
    }
    return false;
}

bool IAController::isGoingLeft() {
    if(character.sprite.getPosition().x - scope < playerPosition.x && !(character.sprite.getPosition().x - (scope / 2) < playerPosition.x)) {
       //printf("\nLEFT");
        return true;
    }
    return false;
}

bool IAController::isJumping() {
    return false;
}

bool IAController::isShooting() {
    if(character.sprite.getPosition().x - (scope / 2) < playerPosition.x && character.sprite.getPosition().x + (scope / 2) > playerPosition.x){
        return true;
    }
    return false;
}

void IAController::setPlayerPosition(Vector2f position){
    playerPosition = position;
}
