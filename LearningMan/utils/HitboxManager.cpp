//
// Created by quent on 04/05/2021.
//

#include "HitboxManager.hpp"
sf::RectangleShape HitboxManager::getHitboxSprite(sf::FloatRect floatRect){
    sf::RectangleShape rectangle(sf::Vector2f(floatRect.width, floatRect.height));
    rectangle.setOutlineColor(sf::Color(255, 0, 0, 0));
    rectangle.setPosition(floatRect.left, floatRect.top);
    return rectangle;
}
