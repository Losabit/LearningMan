#include <iostream>
#include <list>
#include "define.hpp"
#include "controllers/PlayerController.hpp"
#include "controllers/IAController.hpp"
#include "characters/Heros.hpp"
#include "characters/Shotgunner.hpp"
#include "Map/Map.h"
#include "utils/BulletManager.hpp"


using namespace std;

//ToDo
int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.move(0, 580);

    Character shotgunner = Shotgunner();
    IAController shotgunnerController(&shotgunner);
    shotgunnerController.character.sprite.move(600, 575);
    shotgunnerController.character.sprite.setScale(-1, 1);

    list<Controller*> ennemies;
    list<Controller*> :: iterator itEnnemies;
    ennemies.push_back(&shotgunnerController);

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
        }

        /*
            if(  playerController.character.sprite.getGlobalBounds().intersects(map.bigWall.getGlobalBounds())){
               cout << "On touche le mur"<< endl;
            }
            else {
               cout << "On touche pas "<< endl;

            }
        */

        playerController.play();
        for(itEnnemies = ennemies.begin(); itEnnemies != ennemies.end();itEnnemies++){
            (*itEnnemies)->play(playerController.character);
        }

        window.clear(sf::Color(122,160,122,0));
        window.draw(playerController.character.sprite);
        BulletManager::manageBullets(&playerController, &ennemies, &window);
        for(itEnnemies = ennemies.begin(); itEnnemies != ennemies.end();itEnnemies++) {
            window.draw((*itEnnemies)->character.sprite);
            BulletManager::manageBullets((*itEnnemies), &playerController, &window);
        }
        map.drawBackground(window);

        window.display();
    }
    return 0;
}
