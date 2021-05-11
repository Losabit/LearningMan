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
    int WALL_SIZE = 50;
    sf::Sprite platform;
private:
    sf::Texture backgroundTextureMoon;
    sf::Texture TextureBigWall;
    sf::Texture backgroundTextureCloud;
    sf::Texture backgroundTextureMoutain;
    sf::Texture backgroundTexutreGround;
    sf::Texture backgroundTexutreGround2;
    sf::Texture texturePlatform;

    sf::Sprite backgroundMoon;
    sf::Sprite backgroundCloud;
    sf::Sprite backgroundMoutain;
    sf::Sprite backgroundGround;
    sf::Sprite backgroundGround2;

    // Element de la map qui sert de décor, exemple : Lune, Montagne , Nuage etc.
    std::vector<MapEnvironnement> decor;
    MapModel loadAll(std::string path);
    static sf::Sprite loadBackground(sf::Texture &texture,int rl, int rt, int rw, int rh, int x , int y, bool repeat);
};


#endif //LEARNINGMAN_MAP_H
