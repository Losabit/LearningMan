#include <iostream>
#include <list>
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

            cout << map.bigWall.getPosition().x << endl;
            cout << playerController.character.sprite.getPosition().x << endl;

            if(  playerController.character.sprite.getGlobalBounds().intersects(map.bigWall.getGlobalBounds())){
                heros.move(-1);
                cout << "On touche le mur"<< endl;
            }
            else {
                cout << "On touche pas "<< endl;

            }

        }
        Action playerAction = playerController.play();
        shotgunnerController.play();


        if(playerAction == Action::Shoot){
            bullets.push_back(playerController.character.sprite.getPosition());
        }

        window.clear(sf::Color(122,160,122,0));
        window.draw(playerController.character.sprite);
        window.draw(shotgunnerController.character.sprite);
        map.drawBackground(window);
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
