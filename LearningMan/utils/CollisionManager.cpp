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
    int highestOver = -1;
    int highestOverValue = -1;
    for(int i = 0; i < objects.size(); i++){
        if(isOver(i)){
            if(objects[i].getPosition().y < highestOverValue || highestOver == -1){
                highestOverValue = objects[i].getPosition().y;
                highestOver = i;
            }
        }
        else{
            if(types.at(i) == ObjectType::Wall)
                wallCollision(i);
            else
                platformCollision(i);
        }
    }

     if(highestOver != -1) {
         if (types.at(highestOver) == ObjectType::Wall) {
             wallCollision(highestOver);
             controller->GRAVITY_POINT = objects[highestOver].getPosition().y - objects[highestOver].getGlobalBounds().height / 2;
         } else {
             platformCollision(highestOver);
             controller->GRAVITY_POINT = objects[highestOver].getPosition().y - objects[highestOver].getGlobalBounds().height ;
         }
     }
     else{
         controller->GRAVITY_POINT = 583;
     }
}



void CollisionManager::platformCollision(int indice){
    sf::Sprite platform = objects.at(indice);
    if(controller->character.sprite.getPosition().x >= platform.getPosition().x
       && platform.getPosition().x + platform.getGlobalBounds().width > controller->character.sprite.getPosition().x){
        if (controller->character.sprite.getPosition().y <= platform.getGlobalBounds().top) {
            isFalling.at(indice) = true;
        }
    }
    else if(isFalling.at(indice)){
        isFalling.at(indice) = false;
    }
}

bool CollisionManager::isOver(int indice){
    int decalage2 = 8;
    int decalage = 0;
    if(controller->character.sprite.getScale().x > 0){
        decalage = 20;
    }
    sf::Sprite sprite2 = objects.at(indice);
    return  controller->character.sprite.getPosition().x >= sprite2.getPosition().x  + controller->character.sprite.getGlobalBounds().width / 2 - decalage - 5
               && controller->character.sprite.getPosition().x <= sprite2.getPosition().x + sprite2.getGlobalBounds().width - decalage + decalage2 + 5
                && controller->character.sprite.getPosition().y <= sprite2.getPosition().y ;
}

void CollisionManager::wallCollision(int indice) {
    sf::Sprite sprite2 = objects.at(indice);
    float right = sprite2.getPosition().x + sprite2.getGlobalBounds().width + controller->character.sprite.getGlobalBounds().width;
    float left = sprite2.getPosition().x - controller->character.sprite.getLocalBounds().width;
    int decalage2 = 8;
    int decalage = 0;
    if(controller->character.sprite.getScale().x > 0){
        decalage = 20;
    }

    if(controller->character.sprite.getPosition().x >= sprite2.getPosition().x  + controller->character.sprite.getGlobalBounds().width / 2 - decalage
    && controller->character.sprite.getPosition().x <= sprite2.getPosition().x + sprite2.getGlobalBounds().width - decalage + decalage2){
        if(controller->character.sprite.getPosition().y <= sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2) {
            isFalling.at(indice) = true;
            return;
        }
    }
    else if(isFalling.at(indice) && controller->character.sprite.getPosition().x < right && controller->character.sprite.getPosition().x > left){
        isFalling.at(indice) = false;
        if (abs(controller->character.sprite.getPosition().x - abs(left))
            < abs(controller->character.sprite.getPosition().x - abs(right))) {
            controller->character.velocity.x -= controller->character.speed * 4;
        } else {
            controller->character.velocity.x += controller->character.speed * 4;
        }
    }

    if(!isFalling.at(indice) && controller->character.sprite.getPosition().y > sprite2.getPosition().y - sprite2.getGlobalBounds().height / 2){
        if (controller->character.sprite.getPosition().x < sprite2.getPosition().x
            && controller->character.sprite.getPosition().x > left
            && controller->character.sprite.getScale().x > 0) {
            controller->character.sprite.setPosition(left,
                                controller->character.sprite.getPosition().y);
        }

        if (controller->character.sprite.getPosition().x < right
            && controller->character.sprite.getPosition().x > sprite2.getPosition().x + sprite2.getGlobalBounds().width
            && controller->character.sprite.getScale().x < 0){
            controller->character.sprite.setPosition(right,
                                controller->character.sprite.getPosition().y);
        }
    }
}