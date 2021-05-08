#include "Heros.hpp"
#include "../define.hpp"
#include "../utils/TextureManager.hpp"

Heros::Heros() : Character() {
    textureIdle = TextureManager(CHARACTER_ASSETS_PATH "/player/charge.png", IntRect(14, 0, 30, 25));
    textureShoot = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot without FX.png", IntRect(14, 0, 30, 25));
    std::list<std::list<int>> l2 = {{3},
                                    {2},
                                    {1},
                                    {0}};
    textureBullet = TextureManager(CHARACTER_ASSETS_PATH "/player/shoot FX.png", IntRect(14, 0, 50, 26),
                                   l2, 26, 0);

    std::list<std::list<int>> lMoving = {{0},{1},
                                    {2},{3},
                                    {4},{5},
                                    {6},{7}};
    textureMoving = TextureManager(CHARACTER_ASSETS_PATH "/player/move with FX.png", IntRect(14, 0, 30, 25),
                                   lMoving, 26, 0);
    textureDeath = TextureManager(CHARACTER_ASSETS_PATH "/player/death.png", IntRect(14, 0, 30, 25));
    sprite = textureIdle.toSprite();
    bullet = textureBullet.toSprite(3);
}