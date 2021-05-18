#ifndef MAPCREATOR_HITBOXMANAGER_H
#define MAPCREATOR_HITBOXMANAGER_H
#include <SFML/Graphics.hpp>

class HitboxManager  {
public:
    static sf::RectangleShape getHitboxSprite(sf::FloatRect floatRect);
};



#endif //MAPCREATOR_HITBOXMANAGER_H
