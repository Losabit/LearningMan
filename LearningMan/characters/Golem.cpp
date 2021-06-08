#include "Golem.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Golem::Golem() : Character() {
    // attaque 1 : rochers qui tombe du ciel 2eme 
    // attaque 2 : laser 3eme
    // attaque 3 : laser qui sort des yeux 5eme ligne
    // reveil : 4eme
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 20, 70, 50));
    std::list<std::list<int>> l2 = {{0, 1, 2, 3, 4, 5, 6, 7}};
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 150, 70, 50),
                                  l2, 0, 20);

    std::list<std::list<int>> l3 = {{7, 6, 5, 4, 3, 2, 1, 0}};
    TextureManager textureAwake(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 200, 70, 50),
                                l3, 0, 20);
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot FX.png", IntRect(14, 0, 50, 26),
                                   l2, 26, 0);

    std::list<std::list<int>> lDeath = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                        {10, 11, 12, 13}};
    textureDeath = TextureManager(CHARACTER_ASSETS_PATH "/golem/Character_sheet.png", IntRect(10, 720, 70, 80),
                                  lDeath, 100, 100);
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite(3);
    gravityDecalage = -40;
    health = 3;
}