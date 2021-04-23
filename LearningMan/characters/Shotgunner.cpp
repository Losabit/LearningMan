#include "Shotgunner.hpp"
#include "../define.hpp"

Shotgunner::Shotgunner() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/shotgunner/idle.png", IntRect(0,0,30,30));
    sprite = textureIdle.toSprite();
}