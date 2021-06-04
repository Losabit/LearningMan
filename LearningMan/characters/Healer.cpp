//
// Created by Mirii on 04/06/2021.
//

#include "Healer.h"
#include "../define.hpp"
Healer::Healer(): Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/healer/idle.png", IntRect(0,0,60,60));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/healer/heal charge up.png", IntRect(0,0,60,60));
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast FX.png", IntRect(0,0,60,30));
    std::list<std::list<int>> lMoving = {{0},{1},
                                         {2},{3},
                                         {4},{5},
                                         {6},{7}};
    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/healer/run.png", IntRect(0, 0, 40, 33),
            lMoving, 35, 0);
    speed = 2;
    id = "healer";
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();


}
