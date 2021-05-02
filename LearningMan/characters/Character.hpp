#include <SFML/Graphics.hpp>
#include "../utils/TextureManager.hpp"

#ifndef LEARNINGMAN_CHARACTER_H
#define LEARNINGMAN_CHARACTER_H
using namespace sf;

class Character {
public:
    Character();
    void move(int direction);
    void shoot();
    void wait();
    bool canShoot();
    bool takeDamage(int damage);
    Sprite sprite;
    Sprite bullet;
    float bulletSpeed = 5.0f;

    sf::Vector2f velocity;
    float speed = 4;
    bool canJump = true;
    float gravity = 1.0f;
    float jumpHeight = 80;
    int health = 5;

protected:
    TextureManager textureIdle;
    TextureManager textureShoot;
    TextureManager textureBullet;
    float shootCooldown = 1.0f;

private:
    sf::Clock clockBullet;
};
#endif