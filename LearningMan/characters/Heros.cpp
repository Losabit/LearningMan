#include "Heros.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Heros::Heros() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/player/charge.png", IntRect(14, 0, 40, 25));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot without FX.png", IntRect(14, 0, 60, 28));
    std::list<std::list<int>> l2 = {{3},
                                    {2},
                                    {1},
                                    {0}};
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot FX.png", IntRect(14, 0, 50, 26),
                                   l2, 26, 0);

    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/player/move.png", IntRect(14, 0, 40, 25));
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite(3);
}