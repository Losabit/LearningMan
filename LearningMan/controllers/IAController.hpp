#include "Controller.hpp"

#ifndef LEARNINGMAN_IACONTROLLER_HPP
#define LEARNINGMAN_IACONTROLLER_HPP

class IAController : public Controller {
public:
    IAController(Character* character1);
    virtual Action play(Character ennemie);

};


#endif //LEARNINGMAN_IACONTROLLER_HPP