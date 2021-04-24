#include <cmath>
#include "PlayerController.hpp"
#include "SFML/Graphics.hpp"


PlayerController::PlayerController(Character *character1) : Controller(character1)
{

}

Action PlayerController::play(Character ennemie){
    return play();
}

Action PlayerController::play() {
    character.velocity.x *= 0.2f;
    bool doingSomething = false;
    if(Keyboard::isKeyPressed(Keyboard::D)){
        character.velocity.x += character.speed;
        character.sprite.setScale(1, 1);
        doingSomething = true;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Q)){
        character.velocity.x -= character.speed;
        character.sprite.setScale(-1, 1);
        doingSomething = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::Z) && character.canJump) {
        character.canJump = false;
        character.velocity.y = -sqrtf(2.0f * character.gravity * character.jumpHeight);
    }
    if (character.sprite.getPosition().y >= 581 - 20) {
        character.canJump = true;
        character.sprite.setPosition(character.sprite.getPosition().x, 580 - 15);
    } else {
        character.velocity.y += character.gravity;
    }

    if(Keyboard::isKeyPressed(Keyboard::Space)){
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

    character.sprite.move(character.velocity);

    return Action::None;
}