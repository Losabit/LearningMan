#include "Container.hpp"
#include "../define.hpp"
#include <iostream>

Container::Container() {

}

Container::Container(sf::Sprite sprite1, int number1, int leftLag1){
    sprites.push_back(sprite1);
    number = number1;
    leftLag = leftLag1;
    for(int i = 0; i < number; i++){
        textureIndices.push_back(0);
    }
}

void Container::AddSecondarySprite(sf::Sprite sprite1){
    sprites.push_back(sprite1);
}

void Container::changeTextureOf(int indice, int textureIndice){
    textureIndices.at(indice) = textureIndice;
}

void Container::draw(sf::RenderWindow* window, float positionX, float positionY){
    for(int i = 0; i < number; i++){
        sf::Sprite sprite1 = sprites.at(textureIndices.at(i));
        sprite1.move(positionX + leftLag * i, positionY);
        window->draw(sprite1);
    }
}

void Container::reset(int indice) {
    for(int i = 0; i < textureIndices.size(); i++){
        textureIndices.at(i) = indice;
    }
}