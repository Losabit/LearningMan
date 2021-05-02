#include "Controller.hpp"

#ifndef LEARNINGMAN_IACONTROLLER_HPP
#define LEARNINGMAN_IACONTROLLER_HPP

class IAController : public Controller {
public:
    IAController(Character* character1);

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
};


#endif //LEARNINGMAN_IACONTROLLER_HPP
