#include <SFML/Graphics.hpp>

#ifndef LEARNINGMAN_CHARACTER_H
#define LEARNINGMAN_CHARACTER_H
using namespace sf;

class Character {
public:
    Character();
    void move(int direction);
    void shoot();
    Sprite sprite;

protected:
    Texture textureIdle;
    Texture textureShoot;
    int health = 10;
    float speed = 1.0;

};
#endif