#include "Shotgunner.hpp"
#include "../define.hpp"

Shotgunner::Shotgunner() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/idle.png", IntRect(0,0,30,30));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast.png", IntRect(0,0,30,30));
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/shotgun blast FX.png", IntRect(0,0,60,30));

    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();
}