#include <iostream>
#include "define.hpp"
#include "controllers/PlayerController.hpp"
#include "controllers/IAController.hpp"
#include "characters/Heros.hpp"
#include "characters/Shotgunner.hpp"
#include "Map/Map.h"


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
    Map map = Map();


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }

            cout << map.bigWall.getPosition().x << endl;
            cout << playerController.character.sprite.getPosition().x << endl;

            if(  playerController.character.sprite.getGlobalBounds().intersects(map.bigWall.getGlobalBounds())){
                cout << "On touche le mur"<< endl;
            }
            else {
                cout << "On touche pas "<< endl;

            }

        }
        playerController.play();
        shotgunnerController.play();

       window.clear(sf::Color(122,160,122,0));
        window.draw(playerController.character.sprite);
        window.draw(shotgunnerController.character.sprite);
        map.drawBackground(window);
        window.display();
    }

    return 0;
}
