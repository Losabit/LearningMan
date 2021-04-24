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
    sf::Sprite toSprite();
    sf::Sprite toSprite(int number);
    int getSize();

private:
    std::list<std::list<int>> order;
    float topLag;
    float leftLag;

};


#endif //LEARNINGMAN_TEXTURESLAYER_H