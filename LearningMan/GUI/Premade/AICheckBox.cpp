//
// Created by quent on 22/07/2021.
//

#include "AICheckBox.h"
#include "../../define.hpp"
#include <iostream>
AICheckBox::AICheckBox() {
    textureCheckBox.loadFromFile(GUI_ASSETS_PATH "/checkbox.png");

    checkBoxAIUnchecked = sf::Sprite(textureCheckBox, sf::IntRect(15, 65, 75, 75));
    checkBoxAIUnchecked.move(1000, 0);
    checkBoxAIChecked = sf::Sprite(textureCheckBox, sf::IntRect(112, 65, 75, 75));
    checkBoxAIChecked.move(1000, 0);

    textCheckBox.setString("AI Mode");
    textCheckBox.setCharacterSize(24);
    textCheckBox.setFillColor(sf::Color::White);
    textCheckBox.move(900, 20);

    if(!font.loadFromFile("../ressources/policy/OrelegaOne-Regular.ttf")){
        std::cout << "font not find for AICheckBox" << std::endl;
    }
    textCheckBox.setFont(font);
}

void AICheckBox::clickEvent(sf::Vector2f point){
    if(checkBoxAIUnchecked.getGlobalBounds().contains(point) && checkboxClock.getElapsedTime().asSeconds() > 0.3){
        isChecked = !isChecked;
        checkboxClock.restart();
    }
}

void AICheckBox::draw(sf::RenderWindow* window){
    if (isChecked) {
        window->draw(checkBoxAIChecked);
    } else {
        window->draw(checkBoxAIUnchecked);
    }
    window->draw(textCheckBox);
}