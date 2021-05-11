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
#include "utils/CollisionManager.hpp"

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
    sf::Image icon;
    icon.loadFromFile("../assets/others/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.move(0, 583);
    CollisionManager playerCollision(&playerController);

    Character shotgunner = Shotgunner();
    IAController shotgunnerController(&shotgunner);
    shotgunnerController.character.sprite.move(600, 575);
    shotgunnerController.character.sprite.setScale(-1, 1);

    Sprite player =  playerController.character.sprite;
    list<IAController*> ennemies;
    list<IAController*> :: iterator itEnnemies;
    ennemies.push_back(&shotgunnerController);

    sf::View view(sf::FloatRect(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT));

    Map map = Map("../ressources/map1.json");
    playerCollision.addObject(map.walls, ObjectType::Wall);
    playerCollision.addObject(map.platform, ObjectType::Platform);
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
    spriteHealth.setScale(0.02, 0.02);

    Container containerHealth(spriteHealth, 5, 25);

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
                for(int i = 0; i < map.walls.size(); i++) {
                    if(i != 3)
                        std::cout << i << std::endl;

                    playerCollision.checkCollisions();
                }
                if(playerController.play() == Action::ToDestroy){
                    startGame = false;
                    playerController.character.health = 5;
                    //faire un reste de toute les infos
                }

                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    (*itEnnemies)->setPlayerPosition(playerController.character.sprite.getPosition());
                    (*itEnnemies)->play(playerController.character);

                }
                shotgunnerController.setPlayerPosition(playerController.character.sprite.getPosition());
                view.setCenter(playerController.character.sprite.getPosition().x, 500);
                window.setView(view);
            }
        }
        else{
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(button.sprite.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))) {
                    startGame = true;
                }
            }
        }

        window.clear(sf::Color(122,160,122,0));
        if(startGame) {
            containerHealth.number = playerController.character.health;
            containerHealth.setPlayerXPosition(playerController.character.sprite);
            containerHealth.draw(&window);

            if (SHOWHITBOX) {
                window.draw(HitboxManager::getHitboxSprite(playerController.character.sprite.getGlobalBounds()));
                window.draw(HitboxManager::getHitboxSprite(map.platform.getGlobalBounds()));
                for(int i = 0; i < map.walls.size(); i++) {
                    window.draw(HitboxManager::getHitboxSprite(map.walls.at(i).getGlobalBounds()));
                }
            }

            // Pause menu
            if(paused) {
                float x = playerController.character.sprite.getPosition().x - 200;
                float y = 375.0f;
                sf::RectangleShape darkerForeground(sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
                darkerForeground.setPosition(x, y);
                darkerForeground.setFillColor(sf::Color(0, 0, 0, 75));
                window.draw(darkerForeground);

                sf::Text text;
                text.setString("PAUSE");
                text.setPosition(x + 200, 300);
                window.draw(text);
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
