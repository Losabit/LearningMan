#include "PlayerController.hpp"
#include "SFML/Graphics.hpp"


PlayerController::PlayerController(Character *character1) : Controller(character1)
{

}

Action PlayerController::play() {
    bool doingSomething = false;
    if(Keyboard::isKeyPressed(Keyboard::D)){
        doingSomething = true;
        character.move(1);
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q)){
        doingSomething = true;
        character.move(-1);
    }

    if(Keyboard::isKeyPressed(Keyboard::Space)){
        if(character.canShoot()){
            doingSomething = true;
            character.shoot();
            return Action::Shoot;
        }
    }

    if(!doingSomething){
        character.wait();
    }

    return Action::None;
}