#ifndef TESTSFML_BUTTON_HPP
#define TESTSFML_BUTTON_HPP
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(std::string texturePath, sf::IntRect rect1);
    Button(std::string texturePath, sf::IntRect rect1, sf::Text text1);
    Button(std::string texturePath, sf::IntRect rect1, std::string policyPath);

    void draw(sf::RenderWindow* window);
    void setPosition(sf::Vector2f position);
    sf::Text text;
    sf::Sprite sprite;

private:
    sf::Texture texture;
    sf::Font font;
};


#endif //TESTSFML_BUTTON_HPP
