#include "CollisionManager.hpp"


CollisionManager::CollisionManager(Controller *controller1){
    controller = controller1;
}

void CollisionManager::addObject(sf::Sprite sprite, ObjectType objectType) {
    objects.push_back(sprite);
    types.push_back(objectType);
    isFalling.push_back(false);
}

void CollisionManager::addObject(std::vector<sf::Sprite> sprite, ObjectType objectType) {
    for(int i = 0; i < sprite.size(); i++)
    {
        addObject(sprite.at(i), objectType);
    }
}

void CollisionManager::checkCollisions() {
    for(int i = 0; i < objects.size(); i++){
        if(types.at(i) == ObjectType::Wall)
            controller->character.sprite.setPosition(wallCollision(i));
        else
            controller->character.sprite.setPosition(platformCollision(i));
    }
}

sf::Vector2f CollisionManager::platformCollision(int indice){
    sf::Sprite platform = objects.at(indice);
    if(controller->character.sprite.getPosition().x >= platform.getPosition().x
       && platform.getPosition().x + platform.getGlobalBounds().width > controller->character.sprite.getPosition().x){
        if (controller->character.sprite.getPosition().y <= platform.getGlobalBounds().top) {
            controller->GRAVITY_POINT = platform.getPosition().y - platform.getGlobalBounds().height;
            isFalling.at(indice) = true;
        }
    }
    else if(isFalling.at(indice)){
        isFalling.at(indice) = false;
        controller->GRAVITY_POINT = 583;
    }
    return controller->character.sprite.getPosition();
/*
    if (controller->character.sprite.getPosition().x +
                controller->character.sprite.getGlobalBounds().width >
        map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width
        && (sprite.getPosition().x + sprite.getGlobalBounds().width < map.platform.getPosition().x
            || map.platform.getPosition().x + map.platform.getGlobalBounds().width < sprite.getPosition().x + sprite.getGlobalBounds().width)) {
        playerController.GRAVITY_POINT = 563;
    }
    */
}

sf::Vector2f CollisionManager::wallCollision(int indice) {
    sf::Sprite sprite2 = objects.at(indice);
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
            //std::cout << "here" << std::endl;
            controller->GRAVITY_POINT = sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2;
            return sf::Vector2f(controller->character.sprite.getPosition().x,
                                controller->character.sprite.getPosition().y);
        }
    }
    else if(controller->character.sprite.getPosition().y >= sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2){
        float right = sprite2.getPosition().x + sprite2.getGlobalBounds().width + controller->character.sprite.getGlobalBounds().width;
        float left = sprite2.getPosition().x - controller->character.sprite.getLocalBounds().width;

        if(isFalling.at(indice)) {
            //std::cout << "here 2" << std::endl;
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

    return controller->character.sprite.getPosition();
}