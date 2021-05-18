//
// Created by quent on 25/04/2021.
//
#include <SFML/Graphics.hpp>
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

void Button::draw(sf::RenderWindow* window){
    window->draw(sprite);
    window->draw(text);
}

void Button::move(sf::Vector2f position) {
    sprite.setPosition(sprite.getPosition().x + position.x, sprite.getPosition().y + position.y);
    text.setPosition(text.getPosition().x + position.x, text.getPosition().y + position.y);
}

void Button::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    text.setPosition(position);
}
