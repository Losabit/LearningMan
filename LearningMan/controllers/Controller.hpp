#ifndef CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP
#define CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP

#include "../characters/Character.hpp"
#include "../utils/SoundPlayer.hpp"

enum Action {
    None,
    Shoot
};

class Controller {
public:
    Controller(Character* character1);
    Action play();
    Action play(Character ennemi);
    Character character;
    std::list<Vector2f> bullets;
    std::list<int> bulletsOrientation;
    float GRAVITY_POINT =  581 - 20;

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
    Vector2f jumpPosition;
    SoundPlayer sp;
};
#endif


