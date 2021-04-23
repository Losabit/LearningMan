#include <iostream>
#include <list>
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

    list<Vector2f> bullets;
    list<Vector2f> :: iterator it;
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
        Action playerAction = playerController.play();
        shotgunnerController.play();

        if(playerAction == Action::Shoot){
            bullets.push_back(playerController.character.sprite.getPosition());
        }

        window.clear();
        window.draw(playerController.character.sprite);
        window.draw(shotgunnerController.character.sprite);
        for(it = bullets.begin(); it != bullets.end();it++){
            it->x += playerController.character.bulletSpeed;
            playerController.character.bullet.setPosition(it->x, it->y);
            window.draw(playerController.character.bullet);
            if(it->x > 800) { // ou colision
                it = bullets.erase(it);
            }
        }

        window.display();
    }

    return 0;
}
