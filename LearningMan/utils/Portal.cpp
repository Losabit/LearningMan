#include "Portal.hpp"



Portal::Portal(std::string path, sf::Vector2f position) {
    sf::IntRect rect;
    std::list<std::list<int>> format;
    if(path == "../assets/portals/Portal01/Portal001 Sprite Sheet.png"){
        format = {
            { 0, 1, 2, 3, 4, 5 },
            { 6, 7, 8, 9, 10, 11},
            { 12, 13, 14, 15, 16, 17},
            { 18, 19, 20, 21, 22, 23},
            { 24, 25, 26, 27, 28}
        };
        rect = sf::IntRect(0,0,110,110);
        scale = sf::Vector2f(0.5,0.5);
    }

    this->position = position;
    textureManager = TextureManager(path, rect, format, 110, 110);
}

sf::Sprite Portal::getSprite() {
    sf::Sprite sprite = textureManager.getCurrentSprite(position);
    sprite.setScale(scale);
    return sprite;
}