#include "Controller.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);
    Action play();
    Action play(Character ennemie);
    float GRAVITY_POINT =  581 - 20;
private:
    Vector2f jumpPosition;
};