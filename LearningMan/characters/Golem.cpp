#include "Golem.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Golem::Golem() : BossCharacter() {
    // attaque 1 : rochers qui tombe du ciel 2eme 
    // attaque 2 : laser 3eme
    // attaque 3 : laser qui sort des yeux 5eme ligne
    // reveil : 4eme
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 20, 70, 50));

    std::list<std::list<int>> lAwake = {{7, 6, 5, 4, 3, 2, 1, 0}};
    textureAwake = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                  lAwake, 100, 100);

    std::list<std::list<int>> lAttack1 = {{0, 1, 2, 3, 4}};
    textureAttack1 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                    lAttack1, 100, 100);


    std::list<std::list<int>> lAttack2 = {{0, 1, 2, 3, 4, 5, 6}};
    textureAttack2 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                    lAttack2, 100, 100);

    std::list<std::list<int>> lAttack3 = {{0, 1, 2, 3, 4, 5, 6, 7}};
    textureAttack3 = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                    lAttack3, 100, 100);

    std::list<std::list<int>> lDeath = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                        {10, 11, 12, 13}};
    textureDeath = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                  lDeath, 100, 100);


    sprite = textureIdle.toSprite();
    gravityDecalage = -40;
    health = 3;
}