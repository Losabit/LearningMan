#include "Controller.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);
    float GRAVITY_POINT =  581 - 20;

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();
    
private:
    Vector2f jumpPosition;
    SoundPlayer sp;
};