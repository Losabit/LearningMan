//
// Created by quent on 26/07/2021.
//
#include "ModelConfiguration.h"
#include "../../define.hpp"
#include <iostream>
#include <regex>
#include <dirent.h>

ModelConfiguration::ModelConfiguration(){
    modelTexture.loadFromFile(GUI_ASSETS_PATH "/model.png");
    modelSprite = sf::Sprite(modelTexture, sf::IntRect(0, 0, 200, 200));
    modelSprite.setScale(0.5, 0.5);
    modelSprite.move(0, 130);
    if(!font.loadFromFile("../ressources/policy/OrelegaOne-Regular.ttf")){
        std::cout << "font not find" << std::endl;
    }

    currentModelText.setFont(font);
    currentModelText.setCharacterSize(24);
    currentModelText.setFillColor(sf::Color::White);
    currentModelText.move(105, 170);
}

void ModelConfiguration::clickEvent(sf::Vector2f point){
    if (modelSprite.getGlobalBounds().contains(point) && eventClock.getElapsedTime().asSeconds() > 0.3)
    {
        isOpen = !isOpen;
        eventClock.restart();
    }
}

void ModelConfiguration::draw(sf::RenderWindow* window){
    window->draw(modelSprite);
    if(useExistingModel){
        window->draw(currentModelText);
    }
}

void ModelConfiguration::setModel(std::string name){
    useExistingModel = true;
    currentModelName = name;
    currentModelText.setString(currentModelName);
}


std::vector<std::string> ModelConfiguration::getAllModelsName(){
    DIR *dir;
    std::vector<std::string> result;
    std::string buffString;
    struct dirent *ent;
    if ((dir = opendir("../ressources/policyAndActionValueFunction")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            buffString = ent->d_name;
            if(buffString.find(".model") != std::string::npos)
                result.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
        perror ("");
    }
    return result;
}