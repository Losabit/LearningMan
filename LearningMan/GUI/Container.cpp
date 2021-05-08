#include "Container.hpp"
#include "../define.hpp"
#include <iostream>

Container::Container(sf::Sprite sprite1, int number1, int leftLag1, sf::Sprite player){
    sprite = sprite1;
    number = number1;
    leftLag = leftLag1;
    playerXPosition = player.getPosition().x;
}


void Container::draw(sf::RenderWindow* window){
    for(int i = 0; i < number; i++){
        sf::Sprite sprite1 = sprite;
        sprite1.move((playerXPosition / 2) + leftLag * i, WINDOW_HEIGHT - CAMERA_HEIGHT);
        window->draw(sprite1);
    }
}