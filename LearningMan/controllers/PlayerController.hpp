#include "Controller.hpp"

class PlayerController : public Controller {
public:
    PlayerController(Character* character1);
    Action play();

};