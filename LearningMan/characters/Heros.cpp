#include "Heros.hpp"
#include "../define.hpp"

Heros::Heros() : Character() {
    textureIdle.loadFromFile(CHARACTER_ASSETS_PATH "/player/charge.png");
    textureShoot.loadFromFile(CHARACTER_ASSETS_PATH "/player/shoot with FX.png");

    sprite = Sprite(textureIdle,IntRect(0,0,30,28));
}