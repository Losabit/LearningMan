/*
 * #include <iostream>
#include <list>
#include <regex>
#include "../define.hpp"
#include "../controllers/PlayerController.hpp"
#include "../controllers/IAController.hpp"
#include "../controllers/BossController.h"
#include "../characters/Heros.hpp"
#include "../characters/Shotgunner.hpp"
#include "../characters/Healer.h"
#include "../characters/Golem.hpp"
#include "../Map/Map.h"
#include "../utils/BulletManager.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Container.hpp"
#include "../GUI/EndLevelView.h"
#include "../utils/HitboxManager.hpp"
#include "../utils/CollisionManager.hpp"
#include "../utils/Portal.hpp"

using namespace std;

//ToDo
int main() {
    bool onPlatform = false;
    sf::Clock hitboxClock = sf::Clock();
    sf::Clock pauseClock = sf::Clock();
    sf::Clock levelClock;
    bool endLevel = false;
    float pauseCooldown = 0.5f;

    vector<string> mapsName = Map::getAvailableMapNames();
    EndLevelView endLevelView;

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.setPosition(HEROS_INITIAL_POSITION);
    CollisionManager playerCollision(&playerController);

    Map map;
    std::list<Character> ennemiesCharacters;
    list<IAController> ennemiesRef;
    list<IAController*> ennemies;
    list<IAController*> :: iterator itEnnemies;
    list<CollisionManager> ennemiesCollisions;
    BossCharacter boss;
    BossController bossController(&boss);
    Portal portal;
    bool takePortal = false;
    //playerController.character.sprite.setPosition(4000, 475);
    int ennemiesCount = 0;

    bool paused = false;
    bool startGame = false;

    while (window.isOpen())
    {
        if(endLevel){
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(endLevelView.buttonSpriteContinue.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))) {
                    endLevel = false;
                    startGame = false;
                    takePortal = false;
                    levelClock.restart();
                    containerLifebar.reset(0);
                    playerController.character.reset(HEROS_INITIAL_POSITION);
                }
            }
        }
        else if(startGame) {
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
                playerCollision.checkCollisions();

                if(playerController.play() == Action::ToDestroy){
                    startGame = false;
                    playerController.character.reset(HEROS_INITIAL_POSITION);
                    window.setView(initialView);
                    for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                        //(*itEnnemies)->character.reset();
                    }
                }
                else{
                    view.setCenter(playerController.character.sprite.getPosition().x, 500);
                    window.setView(view);
                }

                if(!takePortal) {
                    for(auto itEnnemiCollision = ennemiesCollisions.begin(); itEnnemiCollision != ennemiesCollisions.end(); itEnnemiCollision++){
                        itEnnemiCollision->checkCollisions();

                    }

                    if (playerController.character.sprite.getGlobalBounds().intersects(
                            portal.getSprite().getGlobalBounds())) {
                        playerController.character.sprite.setPosition(map.boss.character.positionX,
                                                                      map.boss.character.positionY);
                        takePortal = true;
                    }

                    for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                        (*itEnnemies)->setPlayerPosition(playerController.character.sprite.getPosition());
                        (*itEnnemies)->play(playerController.character);
                    }
                }
                else {
                    Action actionBoss = bossController.play(playerController.character);
                    if(actionBoss == Action::ToDestroy){
                        endLevel = true;
                        endLevelView.setTime(levelClock.getElapsedTime());
                        endLevelView.setKill(ennemiesCount - ennemies.size());
                        window.setView(initialView);
                    }
                }
            }
        }
        else{
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(checkBoxAIUnchecked.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))
                   && checkboxClock.getElapsedTime().asSeconds() > 0.3) {
                    checkBoxAI = !checkBoxAI;
                    checkboxClock.restart();
                }

                for(auto buttonRef = buttonsMap.begin(); buttonRef != buttonsMap.end(); buttonRef++){
                    if((*buttonRef).sprite.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))) {
                        string choosenMap = MAP_PATH "/" + (*buttonRef).text.getString().toAnsiString() + ".json";
                        map = Map(choosenMap);
                        //impossible de le mettre sous forme de fonction en fonction // problèmes adresses mémoires avec l'héritage sur  les textures
                        ennemiesCharacters.clear();
                        ennemiesRef.clear();
                        ennemies.clear();
                        ennemiesCollisions.clear();

                        if(map.boss.character.id == "golem"){
                            boss = Golem();
                            boss.sprite.setPosition(map.boss.character.positionX, map.boss.character.positionY);
                            boss.sprite.setScale(-1, 1);
                            bossController = BossController(&boss);
                        }

                        containerLifebar.number = boss.health;
                        portal = Portal(map.boss.portal.path, Vector2f(map.boss.portal.positionX, map.boss.portal.positionY));

                        for(int i = 0; i < map.ennemies.size(); i++){
                            Character shotgunner;
                            Character healer;
                            if(map.ennemies.at(i).id == "shotgunner") {
                                shotgunner = Shotgunner();
                                shotgunner.sprite.setPosition(map.ennemies.at(i).positionX, map.ennemies.at(i).positionY);
                                shotgunner.sprite.setScale(-1, 1);
                                shotgunner.canMove = map.ennemies.at(i).canMove;
                                ennemiesCharacters.push_back(shotgunner);
                            }
                            else if(map.ennemies.at(i).id == "healer") {
                                healer = Healer();
                                healer.sprite.setPosition(map.ennemies.at(i).positionX, map.ennemies.at(i).positionY);
                                healer.sprite.setScale(1, 1);
                                healer.canMove = map.ennemies.at(i).canMove;
                                ennemiesCharacters.push_back(healer);
                            }
                            else{
                                std::cout << "ennemie " << map.ennemies.at(i).id << " not found" << std::endl;
                                continue;
                            }


                        }
                        for(auto itEnnemiesCharacters =  ennemiesCharacters.begin(); itEnnemiesCharacters !=  ennemiesCharacters.end(); itEnnemiesCharacters++){
                            ennemiesRef.push_back(IAController(&(*itEnnemiesCharacters)));
                        }
                        for(auto itEnnemiesRef = ennemiesRef.begin(); itEnnemiesRef != ennemiesRef.end(); itEnnemiesRef++){
                            ennemies.push_back(&(*itEnnemiesRef));
                        }
                        for(auto itEnnemi = ennemies.begin(); itEnnemi != ennemies.end(); itEnnemi++){
                            ennemiesCollisions.push_back(CollisionManager(*itEnnemi));
                        }

                        for(auto itEnnemiCollision = ennemiesCollisions.begin(); itEnnemiCollision != ennemiesCollisions.end(); itEnnemiCollision++){
                            itEnnemiCollision->addObject(map.walls, ObjectType::Wall);
                            itEnnemiCollision->addObject(map.platforms, ObjectType::Platform);
                        }

                        playerCollision.clear();
                        //playerCollision.addObject(bossController.character.sprite, ObjectType::Wall);
                        playerCollision.addObject(map.walls, ObjectType::Wall);
                        playerCollision.addObject(map.platforms, ObjectType::Platform);
                        ennemiesCount = ennemies.size();
                        startGame = true;
                        break;
                    }
                }
            }
        }


            if(takePortal){
                for(int i = 0; i < bossController.character.projectiles.size(); i++){
                    window.draw(bossController.character.projectiles.at(i));

                    if(bossController.character.projectiles.at(i).getGlobalBounds().intersects(playerController.character.sprite.getGlobalBounds())){
                        bossController.character.projectiles.erase(bossController.character.projectiles.begin() + i);
                        bossController.character.projectilesMovement.erase(bossController.character.projectilesMovement.begin() + i);
                        i--;
                        playerController.character.takeDamage(1);
                        continue;
                    }

                    if(bossController.character.projectilesMovement.at(i) == ProjectileMovement::Down){
                        bossController.character.projectiles.at(i).move(0, 4);
                        if(bossController.character.projectiles.at(i).getPosition().y > 600){
                            bossController.character.projectiles.erase(bossController.character.projectiles.begin() + i);
                            bossController.character.projectilesMovement.erase(bossController.character.projectilesMovement.begin() + i);
                            bossController.character.projectilesClock.erase(bossController.character.projectilesClock.begin() + i);
                            i--;
                        }
                    }
                    else if(bossController.character.projectilesMovement.at(i) == ProjectileMovement::Immobile){
                        if(bossController.character.projectilesClock.at(i).getElapsedTime().asMilliseconds() > 600){
                            bossController.character.projectiles.erase(bossController.character.projectiles.begin() + i);
                            bossController.character.projectilesMovement.erase(bossController.character.projectilesMovement.begin() + i);
                            bossController.character.projectilesClock.erase(bossController.character.projectilesClock.begin() + i);
                            i--;
                        }
                    }
                }
            }
            else{
                BulletManager::manageBullets(&playerController, &ennemies, map.walls,&window);
                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    window.draw((*itEnnemies)->character.sprite);
                    if((*itEnnemies)->character.id != "healer"){
                        BulletManager::manageBullets((*itEnnemies), &playerController, map.walls, &window);

                    }else{
                        if((*itEnnemies)->character.launchHeal) {
                            Healer::heal((*itEnnemies), &ennemies);
                            (*itEnnemies)->character.launchHeal = false;
                        }
                    }
                }
            }
        }

    }
    return 0;
}
*/