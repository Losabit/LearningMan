#include "Heros.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Heros::Heros() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/player/charge.png", IntRect(0,0,40,28));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot with FX.png", IntRect(0,0,60,28));
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot FX.png", IntRect(0,0,50,20));
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite();
}