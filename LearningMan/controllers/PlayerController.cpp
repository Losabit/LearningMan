#include "PlayerController.hpp"

PlayerController::PlayerController(Character character1) : Controller(character1)
{

}

void PlayerController::play() {
    if(Keyboard::isKeyPressed(Keyboard::D)){
        character.move(1);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q)){
        character.move(-1);
    }
}