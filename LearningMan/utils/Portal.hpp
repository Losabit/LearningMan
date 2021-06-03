#ifndef LEARNINGMAN_PORTAL_HPP
#define LEARNINGMAN_PORTAL_HPP
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureManager.hpp"

class Portal {
public:
    Portal(){};
    Portal(std::string path, sf::Vector2f position);
    sf::Sprite getSprite();
    sf::Vector2f scale;
    sf::Vector2f position;
    TextureManager textureManager;
};


#endif //LEARNINGMAN_PORTAL_HPP
