#ifndef LEARNINGMAN_BOSSCHARACTER_H
#define LEARNINGMAN_BOSSCHARACTER_H
#include "Character.hpp"

enum ProjectileMovement {
    Down,
    Up,
    Left,
    Right,
    Immobile
};

class BossCharacter : public Character {
public:
    BossCharacter();
    void awake();
    bool attack(int i);
    void setTextureOrientation(int orientation);
    std::vector<sf::Sprite> projectiles;
    std::vector<sf::Clock> projectilesClock;
    std::vector<ProjectileMovement> projectilesMovement;

protected:
    TextureManager textureAwake;
    TextureManager textureAttack1;
    TextureManager projectileAttack1;
    TextureManager textureAttack2;
    TextureManager projectileAttack2;
    TextureManager textureAttack3;
    TextureManager projectileAttack3;

private:
    float getCorrectScale(int orientation, float scaleX);
};


#endif //LEARNINGMAN_BOSSCHARACTER_H
