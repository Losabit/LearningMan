//
// Created by Mirii on 20/04/2021.
//

#ifndef LEARNINGMAN_MAP_H
#define LEARNINGMAN_MAP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "../controllers/IAController.hpp"
#include "MapModel.hpp"

class Map {
public:
    Map();
    Map(std::string path);
    void drawBackground(sf::RenderWindow &window);
    static std::vector<std::string> getAvailableMapNames();
    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> platforms;
    std::vector<sf::Sprite> decors;
    std::vector<Ennemie> ennemies;
    Boss boss;
    sf::Color backgroundColor;
private:
    std::map<int, sf::Texture> textures;

    MapModel loadAll(std::string path);
    static sf::Sprite loadBackground(sf::Texture &texture, bool repeat);
};


#endif //LEARNINGMAN_MAP_H
