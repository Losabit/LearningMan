//
// Created by quent on 22/07/2021.
//

#include "ContainerHerosHealth.h"
#include "../../define.hpp"

ContainerHerosHealth::ContainerHerosHealth() : Container() {
    textureHealth.loadFromFile(GUI_ASSETS_PATH "/health.png");
    spriteHealth = sf::Sprite(textureHealth, sf::IntRect(0, 0, 901, 900));
    spriteHealth.setScale(0.02, 0.02);

    sprites.push_back(spriteHealth);
    number = 5;
    leftLag = 25;
    for(int i = 0; i < number; i++){
        textureIndices.push_back(0);
    }
}