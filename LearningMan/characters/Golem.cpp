#include "Golem.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Golem::Golem() : BossCharacter() {
    // attaque 1 : rochers qui tombe du ciel 2eme 
    // attaque 2 : laser 3eme
    // attaque 3 : laser qui sort des yeux 5eme ligne
    // reveil : 4eme
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 20, 60, 50));

    std::list<std::list<int>> lAwake = {{7, 6, 5, 4, 3, 2, 1, 0}};
    textureAwake = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 720, 60, 80),
                                  lAwake, 100, 100);

    std::list<std::list<int>> lAttack1 = {{0, 1, 2, 3, 4}};
    textureAttack1 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 220, 75, 50),
                                    lAttack1, 100, 100);

    std::list<std::list<int>> lAttack2 = {{0, 1, 2, 3, 4, 5}};
    textureAttack2 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 120, 60, 50),
                                    lAttack2, 100, 100);

    std::list<std::list<int>> lAttack3 = {{0, 1, 2, 3, 4, 5, 6, 7}};
    textureAttack3 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 520, 60, 50),
                                    lAttack3, 100, 100);

    projectileAttack2 = TextureManager(CHARACTER_ASSETS_PATH "/golem/rock.png", IntRect(50, 40, 390, 300));
    projectileAttack2.scale = sf::Vector2f(0.1, 0.1);
    projectileAttack1 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Laser_sheet.png", IntRect(40, 910, 300, 45));
    projectileAttack3 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Laser_sheet.png", IntRect(40, 910, 300, 45));

    std::list<std::list<int>> lDeath = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                        {10, 11, 12, 13}};
    textureDeath = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(20, 720, 60, 80),
                                  lDeath, 100, 100);

    sprite = textureIdle.toSprite();
    gravityDecalage = -40;
    health = 10;
}