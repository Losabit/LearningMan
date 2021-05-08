#include "CollisionManager.hpp"


CollisionManager::CollisionManager(Controller *controller1){
    controller = controller1;
}

void CollisionManager::addObject(sf::Sprite sprite) {
    walls.push_back(sprite);
    isFalling.push_back(false);
}

void CollisionManager::addObject(std::vector<sf::Sprite> sprite) {
    for(int i = 0; i < sprite.size(); i++)
    {
        addObject(sprite.at(i));
    }
}

void CollisionManager::checkCollisions() {
    for(int i = 0; i < walls.size(); i++){
        controller->character.sprite.setPosition(wallCollision(i));
    }
}

sf::Vector2f CollisionManager::wallCollision(int indice) {
    sf::Sprite sprite2 = walls.at(indice);
    int decalage2 = 8;
    int decalage = 0;
    //faire ca proprement  + enlever eventuel problemes (utiliser une vraie classe ?)
    if(controller->character.sprite.getScale().x > 0){
        decalage = 20;
    }

    if(controller->character.sprite.getPosition().x >= sprite2.getPosition().x  + controller->character.sprite.getGlobalBounds().width / 2 - decalage
    && controller->character.sprite.getPosition().x <= sprite2.getPosition().x + sprite2.getGlobalBounds().width - decalage + decalage2){
        if(controller->character.sprite.getPosition().y <= sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2) {
            isFalling.at(indice) = true;
            std::cout << "here" << std::endl;
            controller->GRAVITY_POINT = sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2;
            return sf::Vector2f(controller->character.sprite.getPosition().x,
                                controller->character.sprite.getPosition().y);
        }
    }
    else if(controller->character.sprite.getPosition().y >= sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2){
        float right = sprite2.getPosition().x + sprite2.getGlobalBounds().width + controller->character.sprite.getGlobalBounds().width;
        float left = sprite2.getPosition().x - controller->character.sprite.getLocalBounds().width;

        if(isFalling.at(indice)) {
            std::cout << "here 2" << std::endl;
            isFalling.at(indice) = false;
            controller->GRAVITY_POINT = 583;
            if(controller->character.sprite.getPosition().x < right && controller->character.sprite.getPosition().x > left) {
                if (abs(controller->character.sprite.getPosition().x - abs(left))
                    < abs(controller->character.sprite.getPosition().x - abs(right))) {
                    controller->character.sprite.setPosition(
                            left + controller->character.sprite.getLocalBounds().width / 2,
                            controller->character.sprite.getPosition().y);
                } else {
                    controller->character.sprite.setPosition(
                            right - controller->character.sprite.getLocalBounds().width / 2,
                            controller->character.sprite.getPosition().y);
                }
            }
        }


        if (controller->character.sprite.getPosition().x < sprite2.getPosition().x
            && controller->character.sprite.getPosition().x > left
            && controller->character.sprite.getScale().x > 0) {
                return sf::Vector2f(left,
                        controller->character.sprite.getPosition().y);
        }


        if (controller->character.sprite.getPosition().x < right
            && controller->character.sprite.getPosition().x > sprite2.getPosition().x + sprite2.getGlobalBounds().width
            && controller->character.sprite.getScale().x < 0){
            return sf::Vector2f(right,
                                controller->character.sprite.getPosition().y);
        }
    }





    // Gestion des colision en X
/*
    if(sprite.getPosition().x + sprite.getGlobalBounds().width >= map.platform.getPosition().x
       && map.platform.getPosition().x + map.platform.getGlobalBounds().width > sprite.getPosition().x + sprite.getGlobalBounds().width
            ){
        sprite.getPosition().y < map.platform.getGlobalBounds().top;
        if (sprite.getPosition().y < map.platform.getGlobalBounds().top ) {
            if(playerController.GRAVITY_POINT != map.platform.getGlobalBounds().top - map.platform.getGlobalBounds().height ){
                playerController.GRAVITY_POINT = map.platform.getGlobalBounds().top - map.platform.getGlobalBounds().height;
            }
            sprite.setPosition(
                    sprite.getPosition().x,
                    playerController.GRAVITY_POINT + 1);
        }

    }

    if (sprite.getPosition().x +
        sprite.getGlobalBounds().width >
        map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width
        && (sprite.getPosition().x + sprite.getGlobalBounds().width < map.platform.getPosition().x
            || map.platform.getPosition().x + map.platform.getGlobalBounds().width < sprite.getPosition().x + sprite.getGlobalBounds().width)) {
        playerController.GRAVITY_POINT = 563;
    }
    */
     return controller->character.sprite.getPosition();
}