#ifndef LEARNINGMAN_CONTAINER_HPP
#define LEARNINGMAN_CONTAINER_HPP
#include "SFML/Graphics.hpp"

class Container {
public:
    Container(sf::Sprite sprite1, int number1, int leftLag1, bool inX);
    void addText(sf::Text text1, std::vector<std::string> values1);
    void draw(sf::RenderWindow* window);
    void move(sf::Vector2f vector2F);
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;
private:
    int leftLag;
    bool inX = true;

};


#endif //LEARNINGMAN_CONTAINER_HPP
