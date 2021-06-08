#include "Controller.hpp"

#ifndef LEARNINGMAN_IACONTROLLER_HPP
#define LEARNINGMAN_IACONTROLLER_HPP

class IAController : public Controller {
public:
    IAController(Character* character1);
    void setPlayerPosition(Vector2f position);

protected:
    Vector2f playerPosition = Vector2f(0.0f, 0.0f);
    Sprite ennemi;
    float scope = 300.f;
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
    virtual bool isHealing();

};


#endif //LEARNINGMAN_IACONTROLLER_HPP
