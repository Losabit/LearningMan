//
// Created by quent on 22/07/2021.
//

#ifndef LEARNINGMAN_CONTAINERLIFEBAR_H
#define LEARNINGMAN_CONTAINERLIFEBAR_H
#include "../Container.hpp"
#include <SFML/Graphics.hpp>
class ContainerLifebar : public Container{
public:
    ContainerLifebar();
    void draw(sf::RenderWindow* window, float positionX, float positionY);
private:
    sf::Texture lifebar;
    sf::Texture lifebarEmpty;
    sf::Sprite lifebarSprite;
    sf::Sprite lifebarEmptySprite;
};


#endif //LEARNINGMAN_CONTAINERLIFEBAR_H
