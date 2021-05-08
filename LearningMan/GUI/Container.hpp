#ifndef LEARNINGMAN_CONTAINER_HPP
#define LEARNINGMAN_CONTAINER_HPP
#include "SFML/Graphics.hpp"

class Container {
public:
    Container(sf::Sprite sprite1, int number1, int leftLag1, sf::Sprite player);
    void draw(sf::RenderWindow* window);
    int number;
private:
    int leftLag;
    float playerXPosition;
    sf::Sprite sprite;
};


#endif //LEARNINGMAN_CONTAINER_HPP
