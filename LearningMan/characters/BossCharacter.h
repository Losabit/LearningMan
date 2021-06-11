#ifndef LEARNINGMAN_BOSSCHARACTER_H
#define LEARNINGMAN_BOSSCHARACTER_H
#include "Character.hpp"

class BossCharacter : public Character {
public:
    BossCharacter();
    TextureManager textureAwake;
    TextureManager textureAttack1;
    TextureManager textureAttack2;
    TextureManager textureAttack3;
};


#endif //LEARNINGMAN_BOSSCHARACTER_H
