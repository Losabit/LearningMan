#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::TextureManager(std::string path, sf::IntRect rect1)
{
    sf::Texture texture1;
    texture1.loadFromFile(path);
    texture = texture1;
    rect = rect1;
}

TextureManager::TextureManager(std::string path, sf::IntRect rect1,
                               std::list<std::list<int>> order1, float topLag1, float leftLag1) {
    sf::Texture texture1;
    texture1.loadFromFile(path);
    texture = texture1;
    rect = rect1;
    order = order1;
    topLag = topLag1;
    leftLag = leftLag1;
}

sf::Sprite TextureManager::toSprite() {
    return sf::Sprite(texture, rect);
}

