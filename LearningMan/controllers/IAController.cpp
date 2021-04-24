#include "IAController.hpp"

IAController::IAController(Character* character1) : Controller(character1)
{

}

Action IAController::play(Character ennemi) {
    bool doingSomething = false;
    float scopeVision = 100;
    if(ennemi.sprite.getPosition().x + scopeVision > character.sprite.getPosition().x
    && ennemi.sprite.getPosition().x - scopeVision < character.sprite.getPosition().x){
        if(character.canShoot()){
            doingSomething = true;
            character.shoot();
            bullets.push_back(character.sprite.getPosition());
            bulletsOrientation.push_back(character.sprite.getScale().x);
            return Action::Shoot;
        }
    }

    if(!doingSomething){
        character.wait();
    }

    return Action::None;
}