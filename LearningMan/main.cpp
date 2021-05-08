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
#include "utils/HitboxManager.hpp"

using namespace std;

//ToDo
int main() {
    bool onPlatform = false;
    bool SHOWHITBOX = false;
    sf::Clock hitboxClock = sf::Clock();
    sf::Clock pauseClock = sf::Clock();
    float pauseCooldown = 0.5f;
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

    sf::View view(sf::FloatRect(0, 0, 400.f, 250.f));

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
                if(pauseClock.getElapsedTime().asSeconds() > pauseCooldown) {
                    paused = !paused;
                    pauseClock.restart();
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)
            && hitboxClock.getElapsedTime().asSeconds() > 0.5){
                SHOWHITBOX = !SHOWHITBOX;
                hitboxClock.restart();
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

                        else {
                            playerController.GRAVITY_POINT = map.bigWall.getGlobalBounds().top-10;
                            playerController.character.sprite.setPosition(
                                    playerController.character.sprite.getPosition().x,
                                    map.bigWall.getGlobalBounds().top - 10);

                        }

                    }

                }
                // Gestion des colision en X

                if(playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width >= map.platform.getPosition().x
                && map.platform.getPosition().x + map.platform.getGlobalBounds().width > playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width
                ){
                    playerController.character.sprite.getPosition().y < map.platform.getGlobalBounds().top;
                    if (playerController.character.sprite.getPosition().y < map.platform.getGlobalBounds().top ) {
                        if(playerController.GRAVITY_POINT != map.platform.getGlobalBounds().top - map.platform.getGlobalBounds().height ){
                            playerController.GRAVITY_POINT = map.platform.getGlobalBounds().top - map.platform.getGlobalBounds().height;
                        }
                        playerController.character.sprite.setPosition(
                                playerController.character.sprite.getPosition().x,
                                playerController.GRAVITY_POINT + 1);
                    }

                }

                if (playerController.character.sprite.getPosition().x +
                    playerController.character.sprite.getGlobalBounds().width >
                    map.bigWall.getPosition().x + map.bigWall.getGlobalBounds().width
                    && (playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width < map.platform.getPosition().x
                    || map.platform.getPosition().x + map.platform.getGlobalBounds().width < playerController.character.sprite.getPosition().x + playerController.character.sprite.getGlobalBounds().width)) {
                    playerController.GRAVITY_POINT = 563;
                }

                if(playerController.play() == Action::ToDestroy){
                    startGame = false;
                    playerController.character.health = 5;
                    //faire un reste de toute les infos
                }

                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    (*itEnnemies)->play(playerController.character);
                }
                view.setCenter(playerController.character.sprite.getPosition());
                window.setView(view);
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
                window.draw(HitboxManager::getHitboxSprite(playerController.character.sprite.getGlobalBounds()));
                window.draw(HitboxManager::getHitboxSprite(map.platform.getGlobalBounds()));
                window.draw(HitboxManager::getHitboxSprite(map.bigWall.getGlobalBounds()));
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
