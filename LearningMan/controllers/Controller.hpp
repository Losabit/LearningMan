#ifndef CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP
#define CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP

#include "../characters/Character.hpp"
enum Action {
    None,
    Shoot
};

class Controller {
public:
    Controller(Character* character1);
    Action play();
    virtual Action play(Character ennemie);
    Character character;
    std::list<Vector2f> bullets;
    std::list<int> bulletsOrientation;
};
#endif


