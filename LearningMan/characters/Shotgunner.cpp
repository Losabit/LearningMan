#include "Shotgunner.hpp"
#include "../define.hpp"

Shotgunner::Shotgunner() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/idle.png", IntRect(0,0,30,30));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast.png", IntRect(0,0,30,30));
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast FX.png", IntRect(0,0,60,30));
    std::list<std::list<int>> lMoving = {{0},{1},
                                         {2},{3},
                                         {4},{5},
                                         {6},{7}};
    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/run.png", IntRect(0, 0, 40, 33),
                                   lMoving, 35, 0);
    speed = 2;
    id = "shotgunner";
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();
}