#include <iostream>
#include <list>
#include <regex>
#include <ctime>
#include "../define.hpp"
#include "../controllers/PlayerController.hpp"
#include "../controllers/PredefineController.hpp"
#include "../controllers/IAController.hpp"
#include "../controllers/BossController.h"
#include "../characters/Heros.hpp"
#include "../characters/Shotgunner.hpp"
#include "../characters/Healer.h"
#include "../characters/Golem.hpp"
#include "../Map/Map.h"
#include "../utils/BulletManager.hpp"
#include "../GUI/Premade/ModelConfiguration.h"
#include "../utils/HitboxManager.hpp"
#include "../utils/CollisionManager.hpp"
#include "../utils/Portal.hpp"
#include "Environment.h"
#include "BossEnvironment.h"
#include "../utils/curlFunction.h"
#include "trainEnvironment.h"
using namespace std;

TrainEnvironment::TrainEnvironment() {
    model = QLearning(0.1, 0.2, 0.9);
    modelBoss = QLearning(0.1, 0.2, 0.9);
}

void TrainEnvironment::train(){
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("../assets/others/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //Init Heros (AI & normal) + ennemis + boss + collisions
    Character heros = Heros();
    PredefineController predefinePlayerController(&heros);
    Environment env(HEROS_INITIAL_POSITION, sf::Vector2f(3100, 475));
    BossEnvironment bossEnv(475);
    predefinePlayerController.character.sprite.setPosition(HEROS_INITIAL_POSITION);
    CollisionManager predefinePlayerCollision(&predefinePlayerController);



    //Game State Control
    bool takePortal = false;
    int ennemiesCount = 0;
    sf::Clock levelClock;

    vector<PolicyAndActionValueFunction> models;
    bool useModel = false;
    if(useModel){
        models = QLearning::loadFromFile("model_0");
        model.loadModel(models.at(0));
        if(models.size() > 1){
            modelBoss.loadModel(models.at(1));
        }
    }

    if(ONLY_TRAIN_ON_BOSS) {
        predefinePlayerController.character.sprite.setPosition(4000, 475);
        takePortal = true;
    }

    Map map;
    std::list<Character> ennemiesCharacters;
    list<IAController> ennemiesRef;
    list<IAController*> ennemies;
    list<IAController*> :: iterator itEnnemies;
    list<CollisionManager> ennemiesCollisions;
    BossCharacter boss;
    BossController bossController(&boss);
    Portal portal;

    std::string choosenMap = MAP_PATH "/" "Level 1" ".json";
    map = Map(choosenMap);

    if(map.boss.character.id == "golem"){
        boss = Golem();
        boss.sprite.setPosition(map.boss.character.positionX, map.boss.character.positionY);
        boss.sprite.setScale(-1, 1);
        bossController = BossController(&boss);
    }

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

    predefinePlayerCollision.addObject(map.walls, ObjectType::Wall);
    predefinePlayerCollision.addObject(map.platforms, ObjectType::Platform);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string startDateTime = dateFormat(ltm);
    ennemiesCount = ennemies.size();
    int startTimestamp = now;

    while (true)
    {
        predefinePlayerController.GRAVITY_POINT = predefinePlayerCollision.checkCollisionsAndGetNewGravity();
        PredefineAction action;
        if(takePortal){
            action = modelBoss.getAction(
                    bossEnv.getState(predefinePlayerController.character.sprite.getPosition()),
                    bossEnv.getReward(predefinePlayerController, bossController.character.sprite),
                    predefinePlayerController.availableActions());
        }
        else {
            action = model.getAction(
                    env.getState(predefinePlayerController.character.sprite.getPosition()),
                    env.getReward(predefinePlayerController.character.sprite.getPosition()),
                    predefinePlayerController.availableActions());
        }

        if (predefinePlayerController.play(action) == Action::ToDestroy) {
            int deathPos = deathPosition(HEROS_INITIAL_POSITION.x, predefinePlayerController.character.sprite.getPosition().x,
                                     map.boss.portal.positionX, takePortal);
            predefinePlayerController.character.reset(HEROS_INITIAL_POSITION);
            if(SEE_IA_LOGS){
                cout << "victory : false ; time : " << time(0) - startTimestamp << " ; deathPos : " << deathPos << endl;
            }
            break;
        }

        if(!IA_MODE_USER_INPUTS && !ENNEMIES_CAN_PLAY && !takePortal) {
            model.getActionReward(
                    env.getState(predefinePlayerController.character.sprite.getPosition()),
                    env.getReward(predefinePlayerController.character.sprite.getPosition()),
                    false);
        }

        if(!takePortal) {
            for(auto itEnnemiCollision = ennemiesCollisions.begin(); itEnnemiCollision != ennemiesCollisions.end(); itEnnemiCollision++){
                itEnnemiCollision->checkCollisions();
            }

            if (predefinePlayerController.character.sprite.getGlobalBounds().intersects(
                    portal.getSprite().getGlobalBounds())) {
                predefinePlayerController.character.sprite.setPosition(map.boss.character.positionX,
                                                                       map.boss.character.positionY);
                takePortal = true;
            }

            if(ENNEMIES_CAN_PLAY) {
                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    (*itEnnemies)->setPlayerPosition(
                            predefinePlayerController.character.sprite.getPosition());
                    (*itEnnemies)->play(predefinePlayerController.character);
                }
                model.getActionReward(
                        env.getState(predefinePlayerController.character.sprite.getPosition()),
                        env.getReward(predefinePlayerController.character.sprite.getPosition(), predefinePlayerController.character.health),
                        false);
            }
        }
        else {
            Action actionBoss = bossController.play(predefinePlayerController.character);
            if(actionBoss == Action::ToDestroy){
                if(SEE_IA_LOGS){
                    cout << " victory : true ; time : " << time(0) - startTimestamp << endl;
                }
                break;
            }
        }

        if(!takePortal) {
            BulletManager::manageBulletsWithoutPrint(&predefinePlayerController, &ennemies, map.walls);

            for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                if((*itEnnemies)->character.id != "healer"){
                    BulletManager::manageBulletsWithoutPrint((*itEnnemies), &predefinePlayerController, map.walls);
                }
                else if((*itEnnemies)->character.launchHeal) {
                    Healer::heal((*itEnnemies), &ennemies);
                    (*itEnnemies)->character.launchHeal = false;
                }
            }
        }
        else {
            if(bossController.character.health > 0) {
                BulletManager::manageBulletsWithoutPrint(&predefinePlayerController, &bossController, map.walls);
            }

            for(int i = 0; i < bossController.character.projectiles.size(); i++){
                if (bossController.character.projectiles.at(i).getGlobalBounds().intersects(predefinePlayerController.character.sprite.getGlobalBounds())) {
                    bossController.character.eraseProjectile(i);
                    predefinePlayerController.character.takeDamage(1);
                    continue;
                }

                if(bossController.character.projectilesMovement.at(i) == ProjectileMovement::Down){
                    bossController.character.projectiles.at(i).move(0, 4);
                    if(bossController.character.projectiles.at(i).getPosition().y > 600){
                        bossController.character.eraseProjectile(i);
                    }
                }
                else if(bossController.character.projectilesMovement.at(i) == ProjectileMovement::Immobile &&
                        bossController.character.projectilesClock.at(i).getElapsedTime().asMilliseconds() > 600){
                    bossController.character.eraseProjectile(i);
                }
            }

            modelBoss.getActionReward(
                    bossEnv.getState(predefinePlayerController.character.sprite.getPosition()),
                    bossEnv.getReward(predefinePlayerController, bossController.character.sprite),
                    false);
        }
    }
}

