#include "Heros.hpp"
#include "../define.hpp"

Heros::Heros() : Character() {
    Texture texture;
    texture.loadFromFile(CHARACTER_ASSETS_PATH "/player/charge.png");
    sprite = Sprite(texture,IntRect(0,0,30,30));
    Vector2f vector = sprite.getPosition();
    sprite.setPosition(vector.x, vector.y + 100);
}