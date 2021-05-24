#include <iostream>
#include "Button.hpp"


Button::Button(std::string texturePath, sf::IntRect rect1){
    texture.loadFromFile(texturePath);
    sprite = sf::Sprite(texture, rect1);
}

Button::Button(std::string texturePath, sf::IntRect rect1, sf::Text text1){
    texture.loadFromFile(texturePath);
    sprite = sf::Sprite(texture, rect1);
    text = text1;
}

Button::Button(std::string texturePath, sf::IntRect rect1, std::string policyPath){
    if(!font.loadFromFile(policyPath)){
        std::cout << "font not find" << std::endl;
    }
    texture.loadFromFile(texturePath);
    sprite = sf::Sprite(texture, rect1);
    text.setFont(font);
}


void Button::draw(sf::RenderWindow* window){
    window->draw(sprite);
    window->draw(text);
}


void Button::setPosition(sf::Vector2f position) {
    sf::Vector2f difference = sprite.getPosition() - text.getPosition();
    sprite.setPosition(position);
    text.setPosition(position - difference);
}
