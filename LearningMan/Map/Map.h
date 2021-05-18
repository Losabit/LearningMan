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
#include "MapEnvironnement.h"
#include "MapModel.hpp"

class Map {
public:
    Map(std::string path);
    void drawBackground(sf::RenderWindow &window);
    void addWall(float x, float y, int i, int i1, int i2, int i3);
    std::vector<std::string> getAll();
    // Element de la map ou une colision est possible
    std::vector<MapEnvironnement> mapElement;

    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> platforms;
    std::vector<sf::Sprite> decors;
    sf::Color backgroundColor;
private:
    Texture textureGround;
    std::map<int, sf::Texture> textures;
    // Element de la map qui sert de décor, exemple : Lune, Montagne , Nuage etc.
    std::vector<MapEnvironnement> decor;
    MapModel loadAll(std::string path);
    static sf::Sprite loadBackground(sf::Texture &texture, bool repeat);
};


#endif //LEARNINGMAN_MAP_H
