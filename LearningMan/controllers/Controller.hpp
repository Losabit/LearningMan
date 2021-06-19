#ifndef CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP
#define CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP

#include "../characters/Character.hpp"
#include "../utils/SoundPlayer.hpp"

enum Action {
    None,
    Shoot,
    Heal,
    ToDestroy
};

class Controller {
public:
    Controller(Character* character1);
    Action play();
    Action play(Character ennemi);
    Character character;
    std::list<Vector2f> bullets;
    std::list<Vector2f> bulletsOrigin;
    std::list<int> bulletsOrientation;
    float GRAVITY_POINT = 583;

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
    virtual bool isHealing();
    SoundPlayer sp;
    bool startHealAnimation = false;
};
#endif


