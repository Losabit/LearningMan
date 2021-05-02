#include "Controller.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
};