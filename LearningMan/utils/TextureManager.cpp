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

sf::Sprite TextureManager::toSprite(sf::Vector2f position) {
    sf::Sprite sprite(texture, rect);
    sprite.setPosition(position);
    return sprite;
}

sf::Sprite TextureManager::toSprite(int number, sf::Vector2f position) {
    sf::Sprite sprite = toSprite(number);
    sprite.setPosition(position);
    return sprite;
}

sf::Sprite TextureManager::toSprite(int number) {
    bool found = false;
    int x = 0;
    int y = 0;
    std::list<std::list<int>> :: iterator it;
    std::list<int> :: iterator it2;
    for(it = order.begin(); it != order.end(); it++){
        for(it2 = it->begin(); it2 != it->end(); it2++){
            if(*it2 == number){
                found = true;
                break;
            }
            x++;
        }
        if(found){
            break;
        }
        y++;
        x = 0;
    }
    sf::IntRect newRect = rect;
    newRect.left += leftLag * x;
    newRect.top += topLag * y;
    return sf::Sprite(texture, newRect);
}

int TextureManager::getSize() {
    std::list<std::list<int>> :: iterator it;
    std::list<int> :: iterator it2;
    int size = 0;
    for(it = order.begin(); it != order.end(); it++){
        for(it2 = it->begin(); it2 != it->end(); it2++){
            size++;
        }
    }
    return size;
}

