#ifndef LEARNINGMAN_BOSSCONTROLLER_H
#define LEARNINGMAN_BOSSCONTROLLER_H
#include "Controller.hpp"
#include "../characters/BossCharacter.h"

class BossController{
public:
    BossController(BossCharacter* character1);
    void setPlayerPosition(Vector2f position);
    Action play();
    Action play(Character ennemi);
    BossCharacter character;
    float GRAVITY_POINT = 583;

protected:
    Vector2f playerPosition = Vector2f(0.0f, 0.0f);
    Sprite ennemi;
    SoundPlayer sp;
    sf::Clock lastAttackClock;

private:
    int attackIndice = 0;
};


#endif //LEARNINGMAN_BOSSCONTROLLER_H
