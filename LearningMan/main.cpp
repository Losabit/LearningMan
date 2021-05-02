#include <iostream>
#include <list>
#include "define.hpp"
#include "controllers/PlayerController.hpp"
#include "controllers/IAController.hpp"
#include "characters/Heros.hpp"
#include "characters/Shotgunner.hpp"
#include "Map/Map.h"
#include "utils/BulletManager.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"


using namespace std;

//ToDo
int main() {
    int SHOWHITBOX = 1;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.move(0, 583);

    Character shotgunner = Shotgunner();
    IAController shotgunnerController(&shotgunner);
    shotgunnerController.character.sprite.move(600, 575);
    shotgunnerController.character.sprite.setScale(-1, 1);

    Sprite player =  playerController.character.sprite;
    list<Controller*> ennemies;
    list<Controller*> :: iterator itEnnemies;
    ennemies.push_back(&shotgunnerController);

    Map map = Map();
    Button button("../assets/button/simple/12.png",
                  IntRect(40,140,480,480),
                  "../ressources/policy/OrelegaOne-Regular.ttf");
    button.sprite.setScale(0.5,0.5);
    button.setPosition(Vector2f(400,300));
    button.text.setString("Play");
    button.text.setCharacterSize(24);
    button.text.setFillColor(sf::Color::White);
    button.text.move(70, 30);

    Texture textureHealth;
    textureHealth.loadFromFile(GUI_ASSETS_PATH "/health.png");
    Sprite spriteHealth(textureHealth, IntRect(0, 0, 901, 900));
    spriteHealth.setScale(0.05, 0.05);
    Container containerHealth(spriteHealth, 5, 45);

    bool paused = false;
    bool startGame = false;
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

        if(startGame) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                paused = !paused;
            }

            if (!paused) {
                if (playerController.character.sprite.getScale().x > 0) {
                    if (playerController.character.sprite.getPosition().x +
                        playerController.character.sprite.getGlobalBounds().width > map.bigWall.getPosition().x
                        && playerController.character.sprite.getPosition().x +
                           playerController.character.sprite.getGlobalBounds().width <
                           map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width
                            ) {
                        if (playerController.character.sprite.getPosition().y > map.bigWall.getGlobalBounds().top) {
                            playerController.GRAVITY_POINT = 580 - 20;
                            playerController.character.sprite.setPosition(
                                    map.bigWall.getPosition().x -
                                    playerController.character.sprite.getLocalBounds().width,
                                    playerController.character.sprite.getPosition().y);

                        } else {
                            playerController.GRAVITY_POINT = map.bigWall.getGlobalBounds().top;
                            playerController.character.sprite.setPosition(
                                    playerController.character.sprite.getPosition().x,
                                    map.bigWall.getGlobalBounds().top);

                        }
                    }
                }

                if (playerController.character.sprite.getScale().x < 0) {
                    if (playerController.character.sprite.getPosition().x <
                        map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width + 35 && playerController.character.sprite.getPosition().x > map.bigWall.getPosition().x ) {
                        if (playerController.character.sprite.getPosition().y > map.bigWall.getGlobalBounds().top) {
                            playerController.GRAVITY_POINT = 580 - 20;
                            playerController.character.sprite.setPosition(
                                    map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width + 38,
                                    playerController.character.sprite.getPosition().y);

                        }

//                        else {
//                            playerController.GRAVITY_POINT = map.bigWall.getGlobalBounds().top-10;
//                            playerController.character.sprite.setPosition(
//                                    playerController.character.sprite.getPosition().x,
//                                    map.bigWall.getGlobalBounds().top - 10);
//
//                        }

                    }
                    else {
                        playerController.GRAVITY_POINT = 540;
                    }
                }
                // Gestion des colision en X

                if (playerController.character.sprite.getPosition().x +
                    playerController.character.sprite.getGlobalBounds().width >
                    map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width) {
                    playerController.GRAVITY_POINT = 563;
                }
                playerController.play();
                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    (*itEnnemies)->play(playerController.character);
                }
            }
            else {
                // Pause menu
            }
        }
        else{
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(button.sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    startGame = true;
                }
            }
        }

        window.clear(sf::Color(122,160,122,0));
        if(startGame) {
            containerHealth.number = playerController.character.health;
            containerHealth.draw(&window);

            if (SHOWHITBOX) {
                sf::FloatRect boudingBox = playerController.character.sprite.getGlobalBounds();
                sf::RectangleShape rectangle(sf::Vector2f(boudingBox.width, boudingBox.height));
                rectangle.setOutlineColor(sf::Color(255, 0, 0, 0));
                rectangle.setPosition(boudingBox.left, boudingBox.top);
                sf::FloatRect boudingBox2 = map.bigWall.getGlobalBounds();
                sf::RectangleShape rectangle2(sf::Vector2f(boudingBox2.width, boudingBox2.height));
                rectangle2.setOutlineColor(sf::Color(255, 0, 0, 0));
                rectangle2.setPosition(boudingBox2.left, boudingBox2.top);
                window.draw(rectangle);
                window.draw(rectangle2);
            }

            window.draw(playerController.character.sprite);
            BulletManager::manageBullets(&playerController, &ennemies, &window);
            for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                window.draw((*itEnnemies)->character.sprite);
                BulletManager::manageBullets((*itEnnemies), &playerController, &window);
            }

            map.drawBackground(window);

        }
        else{
            button.draw(&window);
        }
        window.display();
    }
    return 0;
}
