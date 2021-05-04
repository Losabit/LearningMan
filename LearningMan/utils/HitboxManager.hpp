#ifndef LEARNINGMAN_HITBOXMANAGER_HPP
#define LEARNINGMAN_HITBOXMANAGER_HPP
#include <SFML/Graphics.hpp>

class HitboxManager  {
public:
    static sf::RectangleShape getHitboxSprite(sf::FloatRect floatRect);
};


#endif //LEARNINGMAN_HITBOXMANAGER_HPP
