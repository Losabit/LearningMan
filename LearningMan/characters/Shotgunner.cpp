#include "Shotgunner.hpp"
#include "../define.hpp"

Shotgunner::Shotgunner() : Character() {
    textureIdle.loadFromFile(CHARACTER_ASSETS_PATH "/shotgunner/idle.png");
    sprite = Sprite(textureIdle,IntRect(0,0,30,30));
}