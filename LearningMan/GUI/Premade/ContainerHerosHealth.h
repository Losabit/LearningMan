//
// Created by quent on 22/07/2021.
//

#ifndef LEARNINGMAN_CONTAINERHEROSHEALTH_H
#define LEARNINGMAN_CONTAINERHEROSHEALTH_H
#include "../Container.hpp"
#include <SFML/Graphics.hpp>

class ContainerHerosHealth : public Container {
public:
    ContainerHerosHealth();

private:
    sf::Texture textureHealth;
    sf::Sprite spriteHealth;
};


#endif //LEARNINGMAN_CONTAINERHEROSHEALTH_H
