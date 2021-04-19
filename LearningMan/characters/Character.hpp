#include <SFML/Graphics.hpp>

#ifndef LEARNINGMAN_CHARACTER_H
#define LEARNINGMAN_CHARACTER_H
using namespace sf;

class Character {
public:
    Character();
    Character(Sprite sprite);
    void move(int direction);
    Sprite sprite;

private:
    float speed = 1.0;

};
#endif