#include "PlayerController.hpp"
#include "SFML/Graphics.hpp"


PlayerController::PlayerController(Character *character1) : Controller(character1)
{

}

Action PlayerController::play(Character ennemie){
    return play();
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
            bullets.push_back(character.sprite.getPosition());
            std::cout << character.sprite.getScale().x << std::endl;
            bulletsOrientation.push_back(character.sprite.getScale().x);
            return Action::Shoot;
        }
    }

    if(!doingSomething){
        character.wait();
    }

    return Action::None;
}