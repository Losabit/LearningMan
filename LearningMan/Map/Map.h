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

class Map {
public:
    Map();
    void drawBackground(sf::RenderWindow &window);
    void addWall();
    // Element de la map ou une colision est possible
    std::vector<MapEnvironnement> mapElement;


    sf::Sprite bigWall;
    int WALL_SIZE = 63;
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

    static sf::Sprite loadBackground(sf::Texture &texture,int rl, int rt, int rw, int rh, int x , int y, bool repeat);
};


#endif //LEARNINGMAN_MAP_H
