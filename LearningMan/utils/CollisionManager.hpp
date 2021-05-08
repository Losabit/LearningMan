#ifndef LEARNINGMAN_COLLISIONMANAGER_HPP
#define LEARNINGMAN_COLLISIONMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "../controllers/Controller.hpp"
#include <vector>

class CollisionManager {
public:
    CollisionManager(Controller* controller1);
    void checkCollisions();
    void addObject(sf::Sprite sprite);
    void addObject(std::vector<sf::Sprite> sprite);

private:
    std::vector<sf::Sprite> walls;
    std::vector<bool> isFalling;
    Controller* controller;
    sf::Vector2f wallCollision(int indice);
};


#endif //LEARNINGMAN_COLLISIONMANAGER_HPP
