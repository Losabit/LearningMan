#include <cmath>
#include "PlayerController.hpp"
#include "SFML/Graphics.hpp"
#include "../utils/SoundPlayer.hpp"


PlayerController::PlayerController(Character *character1) : Controller(character1)
{
    SoundPlayer soundPlayer;
    this->sp = soundPlayer;
}

bool PlayerController::isGoingRight(){
    return Keyboard::isKeyPressed(Keyboard::D);
}

bool PlayerController::isGoingLeft() {
    return Keyboard::isKeyPressed(Keyboard::Q);
}

bool PlayerController::isJumping() {
    return Keyboard::isKeyPressed(Keyboard::Z);
}

bool PlayerController::isShooting() {
    return Keyboard::isKeyPressed(Keyboard::Space);
}
