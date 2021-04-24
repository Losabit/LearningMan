#ifndef LEARNINGMAN_BULLETMANAGER_HPP
#define LEARNINGMAN_BULLETMANAGER_HPP
#include "../controllers/Controller.hpp"



class BulletManager {
public:
    static void manageBullets(Controller* shooter, std::list<Controller*>* ennemies, sf::RenderWindow* window);
    static void manageBullets(Controller* shooter, Controller* ennemies, sf::RenderWindow* window);
};


#endif //LEARNINGMAN_BULLETMANAGER_HPP
