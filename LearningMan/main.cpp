#include <iostream>
#include "define.hpp"
#include "controllers//PlayerController.hpp"
#include "characters/Heros.hpp"

using namespace std;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);


    View viewBack(FloatRect(0.f, 0.f, 800, 700));
    Vector2f oldViewPos(viewBack.getCenter());


    Texture texture;
    texture.loadFromFile(CHARACTER_ASSETS_PATH "/player/charge.png");
    Sprite sprite(texture,IntRect(0,0,30,30));
    Vector2f vector = sprite.getPosition();
    sprite.setPosition(vector.x, vector.y + 100);

    Character heros(sprite);
   /*
    Character heros = Character();
    heros = Heros();
    */
    PlayerController playerController(heros);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }
        }
        playerController.play();
        window.clear();
        window.draw(playerController.character.sprite);
        window.display();
    }

    return 0;
}
