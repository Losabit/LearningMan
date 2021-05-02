#include "IAController.hpp"

IAController::IAController(Character* character1) : Controller(character1) {

}


bool IAController::isGoingRight(){
    return false;
}

bool IAController::isGoingLeft() {
    return false;
}

bool IAController::isJumping() {
    return false;
}

bool IAController::isShooting() {
    return true;
}
