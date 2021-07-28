#ifndef LEARNINGMAN_USERCONFIGURATION_HPP
#define LEARNINGMAN_USERCONFIGURATION_HPP
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class UserConfiguration {
public:
    UserConfiguration();
    std::string getPseudo();
    std::string getToken();
    void saveUser(std::string pseudo1);
    void clickEvent(sf::Vector2f point);
    void keyEvent(int letter);
    void draw(sf::RenderWindow* window);
    bool isOpen = false;
    bool exist = true;
    std::string token;
    std::string pseudo;

private:
    sf::Texture textureWhite;
    sf::Texture textureWhiteSelected;
    sf::Clock eventClock;
    sf::Texture textureUser;
    sf::Sprite userIcon;
    sf::Text textButton;
    sf::Sprite spriteButton;
    sf::Texture textureButton;
    sf::Font font;
    sf::Text textSaveInput;
    sf::Sprite spriteSaveInput;
};


#endif //LEARNINGMAN_USERCONFIGURATION_HPP
