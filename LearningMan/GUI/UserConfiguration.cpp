#include "UserConfiguration.hpp"
#include "../define.hpp"
#include "../utils/curlFunction.h"
#include <iostream>
#include <fstream>


UserConfiguration::UserConfiguration() {
    textureUser.loadFromFile(GUI_ASSETS_PATH "/user.png");
    userIcon = sf::Sprite(textureUser, sf::IntRect(0, 0, 512, 512));
    userIcon.setScale(0.2, 0.2);

    if(!font.loadFromFile("../ressources/policy/OrelegaOne-Regular.ttf")){
        std::cout << "font not find" << std::endl;
    }
    textureButton.loadFromFile("../assets/button/simple/12.png");
    spriteButton = sf::Sprite(textureButton, sf::IntRect(40, 140, 480, 200));
    textButton.setFont(font);

    textButton.setString("Valid");
    textButton.setCharacterSize(24);
    textButton.setFillColor(sf::Color::White);
    textButton.move(70, 30);
    textButton.setPosition(sf::Vector2f(400, 400) - (spriteButton.getPosition() - textButton.getPosition()));
    spriteButton.setPosition(sf::Vector2f(400, 400));
    spriteButton.setScale(0.5, 0.5);

    textureWhite.loadFromFile(GUI_ASSETS_PATH "/fondblanc.png");
    textureWhiteSelected.loadFromFile(GUI_ASSETS_PATH "/selectedfondblanc.png");
    spriteSaveInput = sf::Sprite(textureWhiteSelected, sf::IntRect(0, 0, 901, 750));
    spriteSaveInput.move(400, 320);
    spriteSaveInput.setScale(0.24, 0.06);

    textSaveInput.setFont(font);
    textSaveInput.move(410, 320);
    textSaveInput.setCharacterSize(15);
    textSaveInput.setFillColor(sf::Color::Black);

    std::string myText;
    std::ifstream file("../ressources/user/config.txt");
    if(file.good()) {
        getline(file, myText);
        pseudo = myText.substr(0, myText.find(";"));
        token = myText.substr(myText.find(";") + 1, myText.length());
        file.close();
    }
    else{
        isOpen = true;
        exist = false;
    }
    textSaveInput.setString(pseudo);
}

void UserConfiguration::clickEvent(sf::Vector2f point) {
    if(exist) {
        if (userIcon.getGlobalBounds().contains(point) && eventClock.getElapsedTime().asSeconds() > 0.3) {
            isOpen = !isOpen;
            eventClock.restart();
        }
    }

    if(spriteButton.getGlobalBounds().contains(point) && eventClock.getElapsedTime().asSeconds() > 0.3
    && textSaveInput.getString().toAnsiString().length() > 2){
        saveUser(textSaveInput.getString());
        isOpen = false;
        exist = true;
        eventClock.restart();
    }
}

void UserConfiguration::keyEvent(int letter){
    if(eventClock.getElapsedTime().asSeconds() > 0.1) {
        if (letter == 8) {
            textSaveInput.setString(
                    textSaveInput.getString().toAnsiString().substr(0, textSaveInput.getString().toAnsiString().size() -
                                                                       1));
        } else if(textSaveInput.getString().toAnsiString().length() < 12){
            textSaveInput.setString(
                    textSaveInput.getString().toAnsiString() + static_cast<char>(letter));
        }
        eventClock.restart();
    }
}

void UserConfiguration::saveUser(std::string pseudo1){
    std::ofstream o("../ressources/user/config.txt");
    if(!exist || pseudo1 != pseudo){
        token = getInfo(TOKENURL);
        token = token.substr(1, token.length() - 2);
        pseudo = pseudo1;
        o << pseudo + ";" + token << std::endl;
        addUser(pseudo, "\"" + token + "\"");
    }
    o.close();
}

void UserConfiguration::draw(sf::RenderWindow *window) {
    if(exist) {
        window->draw(userIcon);
    }
    if(isOpen){
        window->draw(spriteButton);
        window->draw(textButton);
        window->draw(spriteSaveInput);
        window->draw(textSaveInput);
    }
}

