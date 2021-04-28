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
    playerController.character.sprite.move(0, 575);
    Sprite player =  playerController.character.sprite;
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


        float bottomSide = map.bigWall.getPosition().y + (map.bigWall.getLocalBounds().height );
        // HITBOX
//        sf::FloatRect  boudingBox = playerController.character.sprite.getGlobalBounds();
//        sf::RectangleShape rectangle(sf::Vector2f(boudingBox.width,boudingBox.height));
//        rectangle.setOutlineColor(sf::Color(255,0,0,0));
//        rectangle.setPosition(boudingBox.left,boudingBox.top);
//        sf::FloatRect  boudingBox2 = map.bigWall.getGlobalBounds();
//        sf::RectangleShape rectangle2(sf::Vector2f(boudingBox2.width,boudingBox2.height));
//        rectangle2.setOutlineColor(sf::Color(255,0,0,0));
//        rectangle2.setPosition(boudingBox2.left,boudingBox2.top);

 // Gestion des colision en X
        if(playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width >  map.bigWall.getPosition().x
         &&  playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width < map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width
         ){
            if( playerController.character.sprite.getPosition().y > map.bigWall.getPosition().y - map.bigWall.getGlobalBounds().height){
                playerController.character.sprite.setPosition(map.bigWall.getPosition().x - playerController.character.sprite.getLocalBounds().width ,playerController.character.sprite.getPosition().y);

            }
            else {
                cout << "la " ;
                playerController.character.sprite.setPosition(playerController.character.sprite.getPosition().x , map.bigWall.getPosition().y - map.bigWall.getGlobalBounds().height - 5);

            }

        }
        playerController.play();
        for(itEnnemies = ennemies.begin(); itEnnemies != ennemies.end();itEnnemies++){
            (*itEnnemies)->play(playerController.character);
        }

        window.clear(sf::Color(122,160,122,0));
        BulletManager::manageBullets(&playerController, &ennemies, &window);
        for(itEnnemies = ennemies.begin(); itEnnemies != ennemies.end();itEnnemies++) {
            window.draw((*itEnnemies)->character.sprite);
            BulletManager::manageBullets((*itEnnemies), &playerController, &window);
        }
//        window.draw(rectangle);
//        window.draw(rectangle2);
        map.drawBackground(window);
        window.draw(playerController.character.sprite);


        window.display();
    }
    return 0;
}
