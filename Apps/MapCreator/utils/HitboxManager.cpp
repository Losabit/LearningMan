#include "HitboxManager.h"
sf::RectangleShape HitboxManager::getHitboxSprite(sf::FloatRect floatRect){
    sf::RectangleShape rectangle(sf::Vector2f(floatRect.width, floatRect.height));
    rectangle.setOutlineColor(sf::Color(255, 0, 0, 0));
    rectangle.setPosition(floatRect.left, floatRect.top);
    return rectangle;
}
