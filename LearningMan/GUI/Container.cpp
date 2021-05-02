#include "Container.hpp"
#include <iostream>

Container::Container(sf::Sprite sprite1, int number1, int leftLag1){
    sprite = sprite1;
    number = number1;
    leftLag = leftLag1;
}


void Container::draw(sf::RenderWindow* window){
    for(int i = 0; i < number; i++){
        sf::Sprite sprite1 = sprite;
        sprite1.move(leftLag * i, 0);
        window->draw(sprite1);
    }
}