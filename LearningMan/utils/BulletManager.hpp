#ifndef LEARNINGMAN_BULLETMANAGER_HPP
#define LEARNINGMAN_BULLETMANAGER_HPP
#include "../controllers/Controller.hpp"
#include "../controllers/IAController.hpp"
#include "../controllers/BossController.h"

class BulletManager {
public:
    static void manageBullets(Controller* shooter, std::list<IAController*>* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window);
    static void manageBullets(Controller* shooter, Controller* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window);
    static void manageBullets(Controller* shooter, BossController* ennemies, std::vector<sf::Sprite> walls, sf::RenderWindow* window);
};


#endif //LEARNINGMAN_BULLETMANAGER_HPP
