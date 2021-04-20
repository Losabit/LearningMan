#include <iostream>
#include "define.hpp"
#include "controllers/PlayerController.hpp"
#include "controllers/IAController.hpp"
#include "characters/Heros.hpp"
#include "characters/Shotgunner.hpp"

using namespace std;

//ToDo
//animations tir en continue
int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.move(0, 100);

    Character shotgunner = Shotgunner();
    IAController shotgunnerController(&shotgunner);
    shotgunnerController.character.sprite.move(600, 100);

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
        shotgunnerController.play();

        window.clear();
        window.draw(playerController.character.sprite);
        window.draw(shotgunnerController.character.sprite);

        window.display();
    }

    return 0;
}
