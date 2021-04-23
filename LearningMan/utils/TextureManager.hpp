#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#ifndef LEARNINGMAN_TEXTURESLAYER_H
#define LEARNINGMAN_TEXTURESLAYER_H


/*
 [[1]]
[[1, 2, 3],
[4, 5, 6]]

 [[1, 3, 5],
 [2, 4, 6]]
 */
//utiliser une struct et classe static pour moins d'espace utilisé ?
class TextureManager {
public:
    TextureManager();
    TextureManager(std::string path, sf::IntRect rect1);
    TextureManager(std::string path, sf::IntRect rect1,
                   std::list<std::list<int>> order1, float topLag1, float leftLag1);
    sf::Texture texture;
    sf::IntRect rect;
    sf::Sprite toSprite();

private:
    std::list<std::list<int>> order;
    float topLag;
    float leftLag;

};


#endif //LEARNINGMAN_TEXTURESLAYER_H
