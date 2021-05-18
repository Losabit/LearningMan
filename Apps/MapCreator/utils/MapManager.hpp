//
// Created by quent on 13/05/2021.
//

#ifndef MAPCREATOR_MAPMANAGER_HPP
#define MAPCREATOR_MAPMANAGER_HPP
#include "../lib/json/json.h"
#include <SFML/Graphics.hpp>

class ObjectCut {
public:
    ObjectCut(Json::Value root);
    int id;
    std::string type;
    int top;
    int left;
    int width;
    int height;
};

class MapCut {
public:
    MapCut();
    MapCut(Json::Value root);
    std::string path;
    std::vector<ObjectCut> objects;
};

class MapManager {
public:
    MapManager(std::string path);
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;
    MapCut mapReferences;
    void draw(sf::RenderWindow &window);
    void move(sf::Vector2f vector2F);
    void save(std::string path, std::vector<sf::Sprite> objects, std::vector<int> ids, sf::Vector3i colors);
private:
    MapCut loadAll(std::string path);
    sf::Sprite loadBackground(std::string path, sf::Texture &spriteTexture, int rl, int rt, int rw, int rh, bool repeat);

};


#endif //MAPCREATOR_MAPMANAGER_HPP
