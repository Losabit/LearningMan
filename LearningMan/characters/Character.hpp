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
    void heal();
    void wait();
    void moving();
    bool canShoot();
    bool canHeal();
    bool takeDamage(int damage);
    bool dying();
    void reset(sf::Vector2f position);
    Sprite sprite;
    Sprite bullet;
    float bulletSpeed = 5.0f;

    sf::Vector2f velocity;
    float speed = 3;
    bool canJump = true;
    float gravity = 1.0f;
    float jumpHeight = 100;
    int health = 5;
    int gravityDecalage = 0;
    std::string id = "null";
protected:
    TextureManager textureIdle;
    TextureManager textureShoot;
    TextureManager textureBullet;
    TextureManager textureMoving;
    TextureManager textureDeath;
    float shootCooldown = 1.0f;

private:
    sf::Clock clockBullet;
};
#endif