#include "Controller.hpp"
#include "../utils/SoundPlayer.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);
    Action play();
    Action play(Character ennemie);
    float GRAVITY_POINT =  581 - 20;
    bool  left = false;
    bool right = true;
    
private:
    Vector2f jumpPosition;
    SoundPlayer sp;
};