#include "Controller.hpp"
#include "../utils/SoundPlayer.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);
    Action play();
    Action play(Character ennemie);
    float GRAVITY_POINT =  581 - 20;
private:
    SoundPlayer sp;
};