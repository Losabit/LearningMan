#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#ifndef LEARNINGMAN_TEXTURESLAYER_H
#define LEARNINGMAN_TEXTURESLAYER_H


/*
 * order :
 [[0]]
[[0, 1, 2],
[3, 4, 5]]
[[0],
 [1]]
 [[0, 2, 4],
 [1, 3, 5]]
 */
//utiliser une struct et classe static pour moins d'espace utilisé ?
//trier un tableau a l'avance pour plus de rapidité
class TextureManager {
public:
    TextureManager();
    TextureManager(std::string path, sf::IntRect rect1);
    TextureManager(std::string path, sf::IntRect rect1,
                   std::list<std::list<int>> order1, float topLag1, float leftLag1);

    sf::Texture texture;
    sf::IntRect rect;
    int size = 1;
    int currentIt = 0;
    sf::Vector2f scale = sf::Vector2f(1.0,1.0);

    sf::Sprite getCurrentSprite();
    sf::Sprite getCurrentSprite(sf::Vector2f position);
    sf::Sprite toSprite();
    sf::Sprite toSprite(sf::Vector2f position);
    sf::Sprite toSprite(int number);
    sf::Sprite toSprite(int number, sf::Vector2f position);

private:
    std::list<std::list<int>> order;
    float topLag;
    float leftLag;
    int getSize();
    sf::Clock clock;
};


#endif //LEARNINGMAN_TEXTURESLAYER_H
