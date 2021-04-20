#ifndef CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP
#define CONTROLLERS_LEARNINGMAN_CONTROLLER_HPP

#include "../characters/Character.hpp"
class Controller {
public:
    Controller(Character* character1);
    void play();
    Character character;
};
#endif


