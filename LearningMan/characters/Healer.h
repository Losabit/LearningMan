//
// Created by Mirii on 04/06/2021.
//
#include "Character.hpp"
#ifndef LEARNINGMAN_HEALER_H
#define LEARNINGMAN_HEALER_H


class Healer : public  Character {

public:
    Healer();
    bool isShooting();
    bool  canshoot(){return false;}

protected:
    float shootCooldown = 2.0f;


};


#endif //LEARNINGMAN_HEALER_H
