//
// Created by quent on 22/07/2021.
//

#include "ContainerLifebar.h"
#include "../../define.hpp"

ContainerLifebar::ContainerLifebar() : Container(){
    lifebar.loadFromFile("../assets/GUI/lifebar.png", sf::IntRect(52, 61, 50, 28));
    lifebarEmpty.loadFromFile("../assets/GUI/lifebar.png", sf::IntRect(190, 61, 50, 28));

    lifebarSprite.setTexture(lifebar);
    lifebarSprite.setPosition(BOSS_LIFEBAR_POSITION_X, 615);
    lifebarSprite.setScale(0.5,0.5);

    lifebarEmptySprite.setTexture(lifebarEmpty);
    lifebarEmptySprite.setPosition(BOSS_LIFEBAR_POSITION_X, 615);
    lifebarEmptySprite.setScale(0.5,0.5);

    sprites.push_back(lifebarSprite);
    number = 10;
    leftLag = 25;
    for(int i = 0; i < number; i++){
        textureIndices.push_back(0);
    }
    AddSecondarySprite(lifebarEmptySprite);
}

void ContainerLifebar::draw(sf::RenderWindow* window, float positionX, float positionY){
    for(int i = 0; i < number; i++){
        sf::Sprite sprite1 = sprites.at(textureIndices.at(i));
        sprite1.move((positionX - sprite1.getPosition().x + BOSS_LIFEBAR_POSITION_X) + leftLag * i, positionY);
        window->draw(sprite1);
    }
}