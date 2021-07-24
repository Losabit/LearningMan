//
// Created by quent on 22/07/2021.
//

#ifndef LEARNINGMAN_AICHECKBOX_H
#define LEARNINGMAN_AICHECKBOX_H
#include <SFML/Graphics.hpp>

class AICheckBox {
public:
    AICheckBox();
    void clickEvent(sf::Vector2f point);
    void draw(sf::RenderWindow* window);
    bool isChecked = false;

private:
    sf::Texture textureCheckBox;
    sf::Clock checkboxClock = sf::Clock();
    sf::Sprite checkBoxAIUnchecked;
    sf::Sprite checkBoxAIChecked;
    sf::Text textCheckBox;
    sf::Font font;

};


#endif //LEARNINGMAN_AICHECKBOX_H
