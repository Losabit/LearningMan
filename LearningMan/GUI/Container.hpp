#ifndef LEARNINGMAN_CONTAINER_HPP
#define LEARNINGMAN_CONTAINER_HPP
#include "SFML/Graphics.hpp"

class Container {
public:
    Container(sf::Sprite sprite1, int number1, int leftLag1);
    void AddSecondarySprite(sf::Sprite sprite1);
    void draw(sf::RenderWindow* window, float positionX, float positionY);
    void changeTextureOf(int indice, int textureIndice);
    int number;

private:
    std::vector<int> textureIndices;
    int leftLag;
    float playerXPosition;
    std::vector<sf::Sprite> sprites;
};


#endif //LEARNINGMAN_CONTAINER_HPP
