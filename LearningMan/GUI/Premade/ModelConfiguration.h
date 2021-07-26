//
// Created by quent on 26/07/2021.
//

#ifndef LEARNINGMAN_MODELCONFIGURATION_H
#define LEARNINGMAN_MODELCONFIGURATION_H
#include <SFML/Graphics.hpp>
#include <vector>

class ModelConfiguration {
public:
    ModelConfiguration();
    bool isOpen = false;
    bool useExistingModel = false;
    void clickEvent(sf::Vector2f point);
    void draw(sf::RenderWindow* window);
    void setModel(std::string name);
    static std::vector<std::string> getAllModelsName();

private:
    sf::Texture modelTexture;
    sf::Sprite modelSprite;
    sf::Clock eventClock;
    sf::Font font;
    sf::Text currentModelText;
    std::string currentModelName;
};


#endif //LEARNINGMAN_MODELCONFIGURATION_H
