#include "Container.hpp"
#include "../define.hpp"
#include <iostream>

Container::Container(sf::Sprite sprite1, int number1, int leftLag1, bool inX1){
    leftLag = leftLag1;
    inX = inX1;
    for(int i = 0; i < number1; i++){
        sf::Sprite sprite = sprite1;
        if(inX) {
            sprite.move(leftLag * i, 0);
        }
        else{
            sprite.move( 0, leftLag * i);
        }
        sprites.push_back(sprite);
    }
}

void Container::addText(sf::Text text1, std::vector<std::string> values1){
    for(int i = 0; i < values1.size(); i++) {
        sf::Text text = text1;
        text.setString(values1.at(i));
        if(inX) {
            text.move(leftLag * i, 0);
        }
        else{
            text.move(0, leftLag * i);
        }
        texts.push_back(text);
    }
}

void Container::move(sf::Vector2f vector2F){
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i).move(vector2F);
        if(i < texts.size()){
            texts.at(i).move(vector2F);
        }
    }
}

void Container::draw(sf::RenderWindow* window){
    for(int i = 0; i < sprites.size(); i++){
        window->draw(sprites.at(i));
        if(i < texts.size()){
            window->draw(texts.at(i));
        }
    }
}