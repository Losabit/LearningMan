#ifndef LEARNINGMAN_COLLISIONMANAGER_HPP
#define LEARNINGMAN_COLLISIONMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "../controllers/Controller.hpp"
#include <vector>

enum ObjectType{
    Wall,
    Platform,
    Decor
};

class CollisionManager {
public:
    CollisionManager(Controller* controller1);
    void checkCollisions();
    void addObject(sf::Sprite sprite, ObjectType objectType);
    void addObject(std::vector<sf::Sprite> sprite, ObjectType objectType);
    void clear();

private:
    std::vector<sf::Sprite> objects;
    std::vector<ObjectType> types;
    std::vector<bool> isFalling;
    Controller* controller;
    void wallCollision(int indice);
    void platformCollision(int indice);
    bool isOver(int indice);
};


#endif //LEARNINGMAN_COLLISIONMANAGER_HPP
