#ifndef LEARNINGMAN_PREDEFINECONTROLLER_HPP
#define LEARNINGMAN_PREDEFINECONTROLLER_HPP
#include "Controller.hpp"

enum PredefineAction {
    LeftAction,
    RightAction,
    JumpAction,
    JumpRightAction,
    JumpLeftAction,
    ShootRightAction,
    ShootLeftAction,
    ShootAction,
    WaitAction
};

class PredefineController : public Controller {
public:
    PredefineController(Character* character1);
    PredefineController(Character* character1, std::vector<int> actions1);
    Action play(PredefineAction action);
    static PredefineAction getActionFromInputs();
    float GRAVITY_POINT = 583;
    std::vector<int> actions;

protected:
    virtual bool isGoingRight();
    virtual bool isGoingLeft();
    virtual bool isJumping();
    virtual bool isShooting();

private:
    int actualActionIndice = 0;
    Vector2f jumpPosition;
    SoundPlayer sp;
};


#endif //LEARNINGMAN_PREDEFINECONTROLLER_HPP
