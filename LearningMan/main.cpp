#include <iostream>
#include <list>
#include <regex>
#include <ctime>
#include "define.hpp"
#include "controllers/PlayerController.hpp"
#include "controllers/PredefineController.hpp"
#include "controllers/IAController.hpp"
#include "controllers/BossController.h"
#include "characters/Heros.hpp"
#include "characters/Shotgunner.hpp"
#include "characters/Healer.h"
#include "characters/Golem.hpp"
#include "Map/Map.h"
#include "utils/BulletManager.hpp"
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "GUI/EndLevelView.h"
#include "GUI/UserConfiguration.hpp"
#include "GUI/Premade/ContainerLifebar.h"
#include "GUI/Premade/ContainerHerosHealth.h"
#include "GUI/Premade/AICheckBox.h"
#include "GUI/Premade/ModelConfiguration.h"
#include "utils/HitboxManager.hpp"
#include "utils/CollisionManager.hpp"
#include "utils/Portal.hpp"
#include "learningAlgorithms/QLearning.hpp"
#include "learningAlgorithms/Environment.h"
#include "learningAlgorithms/BossEnvironment.h"
#include "utils/curlFunction.h"

using namespace std;

//ToDo
int main() {
    std::string str ("Test string");
    std::cout << "max_size: " << str.max_size() << "\n";

    // Window + View
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("../assets/others/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::View view(sf::FloatRect(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT));
    sf::View initialView = window.getView();

    // GUI
    vector<string> mapsName = Map::getAvailableMapNames();
    list<Button> buttonsMap;
    Button button("../assets/button/simple/12.png",
                  IntRect(40, 140, 480, 200),
                  "../ressources/policy/OrelegaOne-Regular.ttf");
    button.sprite.setScale(0.5, 0.5);
    button.text.setCharacterSize(24);
    button.text.setFillColor(sf::Color::White);
    button.text.move(70, 30);
    for(int i = 0; i < mapsName.size(); i++) {
        button.setPosition(Vector2f(400, 200 + 100 * i));
        button.text.setString(std::regex_replace(mapsName.at(i), std::regex("\\.json"), ""));
        buttonsMap.push_back(button);
    }

    ContainerLifebar containerLifebar;
    ContainerHerosHealth containerHerosHealth;
    AICheckBox aiCheckBox;
    EndLevelView endLevelView;
    UserConfiguration userConfiguration;
    ModelConfiguration modelConfiguration;

    vector<string> modelsName = ModelConfiguration::getAllModelsName();
    list<Button> buttonsModel;
    Button buttonModel("../assets/button/simple/12.png",
                  IntRect(40, 140, 480, 200),
                  "../ressources/policy/OrelegaOne-Regular.ttf");
    buttonModel.sprite.setScale(0.5, 0.5);
    buttonModel.text.setCharacterSize(24);
    buttonModel.text.setFillColor(sf::Color::White);
    buttonModel.text.move(65, 30);
    for(int i = 0; i < modelsName.size(); i++) {
        buttonModel.setPosition(Vector2f(400, 100 * i));
        buttonModel.text.setString(std::regex_replace(modelsName.at(i), std::regex("\\.model"), ""));
        buttonsModel.push_back(buttonModel);
    }

    //Init Heros (AI & normal) + ennemis + boss + collisions
    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.setPosition(HEROS_INITIAL_POSITION);
    CollisionManager playerCollision(&playerController);

    PredefineController predefinePlayerController(&heros);
    QLearning model(0.5, 0.1, 0.9);
    QLearning modelBoss(0.1, 0.2, 0.9);
    Environment env(HEROS_INITIAL_POSITION, sf::Vector2f(3100, 475));
    BossEnvironment bossEnv(475);
    predefinePlayerController.character.sprite.setPosition(HEROS_INITIAL_POSITION);
    CollisionManager predefinePlayerCollision(&predefinePlayerController);

    Map map;
    std::list<Character> ennemiesCharacters;
    list<IAController> ennemiesRef;
    list<IAController*> ennemies;
    list<IAController*> :: iterator itEnnemies;
    list<CollisionManager> ennemiesCollisions;
    BossCharacter boss;
    BossController bossController(&boss);
    Portal portal;

    //Game State Control
    bool takePortal = false;
    int ennemiesCount = 0;
    bool paused = false;
    int gameNumber = 1;
    bool startGame = false;
    bool endLevel = false;
    int choosenMapIndice = 0;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string startDateTime = dateFormat(ltm);
    int startTimestamp = 0;

    bool showRewardsCases = false;
    bool showStatesCases = false;
    bool SHOWHITBOX = false;

    sf::Clock keyClock = sf::Clock();
    float keyCooldown = 0.5f;
    sf::Clock clickClock = sf::Clock();
    float clickCooldown = 0.5f;
    sf::Clock levelClock;

    vector<PolicyAndActionValueFunction> models;

    if(ONLY_TRAIN_ON_BOSS) {
        playerController.character.sprite.setPosition(4000, 475);
        predefinePlayerController.character.sprite.setPosition(4000, 475);
        takePortal = true;
    }

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

        //ToGo INIT + KEY/CLICK EVENT
        //Main Menu
        if(!startGame && !endLevel){
            if (event.type == sf::Event::TextEntered && userConfiguration.isOpen) {
                userConfiguration.keyEvent(event.text.unicode);
            }

            if(userConfiguration.isOpen && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                userConfiguration.clickEvent(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)));
            }
            else if(modelConfiguration.isOpen && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
            && clickClock.getElapsedTime().asSeconds() > clickCooldown){
                modelConfiguration.clickEvent(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)));
                for(auto buttonRef = buttonsModel.begin(); buttonRef != buttonsModel.end(); buttonRef++){
                    if((*buttonRef).sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        modelConfiguration.setModel((*buttonRef).text.getString().toAnsiString());
                        modelConfiguration.isOpen = false;
                        models = QLearning::loadFromFile((*buttonRef).text.getString().toAnsiString());
                        model.loadModel(models.at(0));
                        if(models.size() > 1){
                            modelBoss.loadModel(models.at(1));
                        }
                        clickClock.restart();
                    }
                }
            }
            else if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && clickClock.getElapsedTime().asSeconds() > clickCooldown)
            || (AUTO_RESTART && aiCheckBox.isChecked && choosenMapIndice != 0))
            {
                clickClock.restart();
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    userConfiguration.clickEvent(
                            window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)));
                    modelConfiguration.clickEvent(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)));
                    aiCheckBox.clickEvent(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)));
                }

                int it = 0;
                for(auto buttonRef = buttonsMap.begin(); buttonRef != buttonsMap.end(); buttonRef++){
                    it++;
                    if((*buttonRef).sprite.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))
                       || (aiCheckBox.isChecked && AUTO_RESTART && choosenMapIndice == it)){
                        choosenMapIndice = it;
                        string choosenMap = MAP_PATH "/" + (*buttonRef).text.getString().toAnsiString() + ".json";
                        map = Map(choosenMap);

                        //impossible de mettre le code du if sous forme de fonction // problèmes adresses mémoires avec l'héritage sur  les textures
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

                        if(aiCheckBox.isChecked){
                            predefinePlayerCollision.clear();
                            predefinePlayerCollision.addObject(map.walls, ObjectType::Wall);
                            predefinePlayerCollision.addObject(map.platforms, ObjectType::Platform);
                        }
                        else {
                            playerCollision.clear();
                            playerCollision.addObject(map.walls, ObjectType::Wall);
                            playerCollision.addObject(map.platforms, ObjectType::Platform);
                        }
                        ennemiesCount = ennemies.size();
                        startGame = true;
                        time_t now = time(0);
                        startTimestamp = now;
                        levelClock.restart();
                        break;
                    }
                }
            }
        }
        else if(startGame) { // In game events
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (keyClock.getElapsedTime().asSeconds() > keyCooldown) {
                    paused = !paused;
                    keyClock.restart();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)
                       && keyClock.getElapsedTime().asSeconds() > keyCooldown && ACTIVE_DEBUG_KEYS) {
                SHOWHITBOX = !SHOWHITBOX;
                keyClock.restart();
            }

            if (keyClock.getElapsedTime().asSeconds() > keyCooldown && aiCheckBox.isChecked) {
                if (paused) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        PolicyAndActionValueFunction policyAndActionValueFunction = model.compile();
                        PolicyAndActionValueFunction policyAndActionValueFunctionBoss;
                        if(takePortal){
                            policyAndActionValueFunctionBoss = modelBoss.compile();
                        }
                        modelBoss.save(policyAndActionValueFunction, policyAndActionValueFunctionBoss);
                        cout << "policyAndActionValueFunction saved" << endl;
                        keyClock.restart();
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                        endLevel = true;
                        startGame = false;
                        if(ONLY_TRAIN_ON_BOSS) {
                            predefinePlayerController.character.sprite.setPosition(4000, 475);
                        }
                        else{
                            predefinePlayerController.character.reset(HEROS_INITIAL_POSITION);
                        }
                        paused = false;
                        keyClock.restart();
                    }
                } else {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && ACTIVE_DEBUG_KEYS) {
                        showStatesCases = !showStatesCases;
                        keyClock.restart();
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ACTIVE_DEBUG_KEYS) {
                        showRewardsCases = !showRewardsCases;
                        keyClock.restart();
                    }
                }
            }
        }
        else if(endLevel){ // End Level View
            if ((event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
            endLevelView.buttonSpriteContinue.getGlobalBounds().contains( window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y))))
            || (AUTO_RESTART && aiCheckBox.isChecked))
            {
                endLevel = false;
                startGame = false;
                levelClock.restart();
                containerLifebar.reset(0);
                if(!ONLY_TRAIN_ON_BOSS){
                    takePortal = false;
                    predefinePlayerController.character.reset(HEROS_INITIAL_POSITION);
                    playerController.character.reset(HEROS_INITIAL_POSITION);
                }
                else{
                    predefinePlayerController.character.reset(sf::Vector2f(4000, 475));
                    playerController.character.reset(sf::Vector2f(4000, 475));
                }

                if(aiCheckBox.isChecked) {
                    bossEnv.reset();
                }
            }
        }


        //ToGo GAME MANAGER
        if(startGame && !paused) {
            bool herosIsDead = false;
            int deathPos;
            if(aiCheckBox.isChecked){
                predefinePlayerController.GRAVITY_POINT = predefinePlayerCollision.checkCollisionsAndGetNewGravity();
                PredefineAction action;
                if(IA_MODE_USER_INPUTS){
                    action = PredefineController::getActionFromInputs();
                }
                else {
                    if(takePortal){
                        if(modelConfiguration.useExistingModel){
                            action = modelBoss.getAction(
                                    bossEnv.getState(predefinePlayerController.character.sprite.getPosition()),
                                    bossEnv.getReward(predefinePlayerController, bossController.character.sprite),
                                    predefinePlayerController.availableActions());
                        }
                        else {
                            action = modelBoss.getAction(
                                    bossEnv.getState(predefinePlayerController.character.sprite.getPosition()),
                                    bossEnv.getReward(predefinePlayerController, bossController.character.sprite),
                                    predefinePlayerController.availableActions());
                        }
                    }
                    else {
                        if(modelConfiguration.useExistingModel) {
                            action = model.getAction(
                                    env.getState(predefinePlayerController.character.sprite.getPosition()),
                                    env.getReward(predefinePlayerController.character.sprite.getPosition()),
                                    predefinePlayerController.availableActions());
                        }
                        else {
                            action = model.getAction(
                                    env.getState(predefinePlayerController.character.sprite.getPosition()),
                                    env.getReward(predefinePlayerController.character.sprite.getPosition()),
                                    predefinePlayerController.availableActions());
                        }
                    }
                    //model.debug(60.0);
                }

                if (predefinePlayerController.play(action) == Action::ToDestroy) {
                    herosIsDead = true;
                    deathPos = deathPosition(HEROS_INITIAL_POSITION.x, predefinePlayerController.character.sprite.getPosition().x,
                                              map.boss.portal.positionX, takePortal);
                    predefinePlayerController.character.reset(HEROS_INITIAL_POSITION);
                } else {
                    view.setCenter(predefinePlayerController.character.sprite.getPosition().x, 500);
                    window.setView(view);
                }

                if(!IA_MODE_USER_INPUTS && !ENNEMIES_CAN_PLAY && !takePortal) {
                    model.getActionReward(
                            env.getState(predefinePlayerController.character.sprite.getPosition()),
                            env.getReward(predefinePlayerController.character.sprite.getPosition()),
                            false);
                }
            }
            else {
                playerCollision.checkCollisions();
                if (playerController.play() == Action::ToDestroy) {
                    herosIsDead = true;
                    deathPos = deathPosition(HEROS_INITIAL_POSITION.x, playerController.character.sprite.getPosition().x,
                                              map.boss.portal.positionX, takePortal);
                    if(ONLY_TRAIN_ON_BOSS) {
                        playerController.character.sprite.setPosition(4000, 475);;
                    }
                    else {
                        playerController.character.reset(HEROS_INITIAL_POSITION);
                    }
                } else {
                    view.setCenter(playerController.character.sprite.getPosition().x, 500);
                    window.setView(view);
                }
            }

            if(herosIsDead) {
                time_t now = time(0);
                endLevelView.maximumTime();
                endLevelView.setKill(ennemiesCount - ennemies.size());
                if (SEND_HTTP_REQUEST) {
                    PolicyAndActionValueFunction policyAndActionValueFunction = model.compile();
                    PolicyAndActionValueFunction policyAndActionValueFunctionBoss;
                    if(takePortal){
                        policyAndActionValueFunctionBoss = modelBoss.compile();
                    }
                    addGame(startDateTime, now - startTimestamp, "\"" + userConfiguration.token + "\"", 1, aiCheckBox.isChecked ? 1 : 0,
                            endLevelView.score, ennemiesCount - ennemies.size(), deathPos,
                            aiCheckBox.isChecked ? QLearning::getModel(policyAndActionValueFunction, policyAndActionValueFunctionBoss) : "NULL");
                }
                if(SEE_IA_LOGS){
                    cout << gameNumber << " -> victory : false ; time : " << now - startTimestamp << " ; deathPos : " << deathPos << endl;
                    gameNumber++;
                }
                endLevel = true;
                startGame = false;
                window.setView(initialView);
                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    //(*itEnnemies)->character.reset();
                }
            }

            if(!takePortal) {
                for(auto itEnnemiCollision = ennemiesCollisions.begin(); itEnnemiCollision != ennemiesCollisions.end(); itEnnemiCollision++){
                    itEnnemiCollision->checkCollisions();
                }
                if(aiCheckBox.isChecked){
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
            }
            else {
                Action actionBoss = bossController.play(aiCheckBox.isChecked ? predefinePlayerController.character : playerController.character);
                if(actionBoss == Action::ToDestroy){
                    endLevel = true;
                    startGame = false;
                    endLevelView.setTime(levelClock.getElapsedTime());
                    endLevelView.setKill(ennemiesCount - ennemies.size());
                    time_t now = time(0);
                    if(SEND_HTTP_REQUEST) {
                        PolicyAndActionValueFunction policyAndActionValueFunction = model.compile();
                        PolicyAndActionValueFunction policyAndActionValueFunctionBoss;
                        if(takePortal){
                            policyAndActionValueFunctionBoss = modelBoss.compile();
                        }
                        addGame(startDateTime, now - startTimestamp, "\"" + userConfiguration.token + "\"", 0,
                                aiCheckBox.isChecked ? 1 : 0, endLevelView.score, ennemiesCount - ennemies.size(), 100,
                                aiCheckBox.isChecked ? QLearning::getModel(policyAndActionValueFunction, policyAndActionValueFunctionBoss) : "NULL");
                    }
                    if(SEE_IA_LOGS){
                        cout << gameNumber << " -> victory : true ; time : " << now - startTimestamp << endl;
                        gameNumber++;
                    }
                    window.setView(initialView);
                }
            }
        }


        //ToGo DRAW + BULLETS
        if(!startGame && !endLevel){
            window.clear(DEFAULT_COLOR);
            userConfiguration.draw(&window);
            if(!userConfiguration.isOpen && !modelConfiguration.isOpen) {
                for (auto buttonRef = buttonsMap.begin(); buttonRef != buttonsMap.end(); buttonRef++) {
                    (*buttonRef).draw(&window);
                }
                aiCheckBox.draw(&window);
            }
            if(aiCheckBox.isChecked) {
                modelConfiguration.draw(&window);
                if(modelConfiguration.isOpen){
                    for (auto buttonRef = buttonsModel.begin(); buttonRef != buttonsModel.end(); buttonRef++) {
                        (*buttonRef).draw(&window);
                    }
                }
            }
        }
        else if(startGame) {
            window.clear(map.backgroundColor);

            if (takePortal) {
                containerLifebar.draw(&window, aiCheckBox.isChecked ? predefinePlayerController.character.sprite.getPosition().x
                                      : playerController.character.sprite.getPosition().x, 0);
            }
            containerHerosHealth.number = aiCheckBox.isChecked ? predefinePlayerController.character.health : playerController.character.health;
            containerHerosHealth.draw(&window, (aiCheckBox.isChecked ? predefinePlayerController.character.sprite.getPosition().x :
                                                playerController.character.sprite.getPosition().x) - 200,WINDOW_HEIGHT - CAMERA_HEIGHT - 50);


            if (SHOWHITBOX) {
                window.draw(HitboxManager::getHitboxSprite(playerController.character.sprite.getGlobalBounds()));
                for(int i = 0; i < map.walls.size(); i++) {
                    window.draw(HitboxManager::getHitboxSprite(map.walls.at(i).getGlobalBounds()));
                }
                for(int i = 0; i < map.platforms.size(); i++) {
                    window.draw(HitboxManager::getHitboxSprite(map.platforms.at(i).getGlobalBounds()));
                }
                for(itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++){
                    window.draw(HitboxManager::getHitboxSprite((*itEnnemies)->character.sprite.getGlobalBounds()));
                }
                if(takePortal){
                    for(int i = 0; i < bossController.character.projectiles.size(); i++){
                        window.draw(HitboxManager::getHitboxSprite(bossController.character.projectiles.at(i).getGlobalBounds()));
                    }
                    window.draw(HitboxManager::getHitboxSprite(bossController.character.sprite.getGlobalBounds()));
                }
            }

            // Pause menu
            if(paused) {
                float x = aiCheckBox.isChecked ? predefinePlayerController.character.sprite.getPosition().x - 200 : playerController.character.sprite.getPosition().x - 200;
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

            map.drawBackground(window);
            window.draw(aiCheckBox.isChecked ? predefinePlayerController.character.sprite : playerController.character.sprite);

            if(!takePortal) {
                //cout << "before player shoot" << endl;
                if(!paused) {
                    if (aiCheckBox.isChecked) {
                        BulletManager::manageBullets(&predefinePlayerController, &ennemies, map.walls, &window);
                    } else {
                        BulletManager::manageBullets(&playerController, &ennemies, map.walls, &window);
                    }
                }
                //cout << "after player shoot" << endl;

                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    window.draw((*itEnnemies)->character.sprite);
                    if((*itEnnemies)->character.id != "healer"){
                        if(!paused) {
                            if (aiCheckBox.isChecked) {
                                BulletManager::manageBullets((*itEnnemies), &predefinePlayerController, map.walls,
                                                             &window);
                            } else {
                                BulletManager::manageBullets((*itEnnemies), &playerController, map.walls, &window);
                            }
                        }
                    }
                    else if((*itEnnemies)->character.launchHeal) {
                        Healer::heal((*itEnnemies), &ennemies);
                        (*itEnnemies)->character.launchHeal = false;
                    }
                }
                window.draw(portal.getSprite());
            }
            else {
                int healthBefore = bossController.character.health;
                if(bossController.character.health > 0) {
                    if(!paused) {
                        if (aiCheckBox.isChecked) {
                            BulletManager::manageBullets(&predefinePlayerController, &bossController, map.walls,
                                                         &window);
                        } else {
                            BulletManager::manageBullets(&playerController, &bossController, map.walls, &window);
                        }
                    }

                    if (healthBefore != bossController.character.health) {
                        containerLifebar.changeTextureOf(bossController.character.health, 1);
                    }
                }

                window.draw(bossController.character.sprite);

                for(int i = 0; i < bossController.character.projectiles.size(); i++){
                    window.draw(bossController.character.projectiles.at(i));
                    if(aiCheckBox.isChecked){
                        if (bossController.character.projectiles.at(i).getGlobalBounds().intersects(predefinePlayerController.character.sprite.getGlobalBounds())) {
                            bossController.character.eraseProjectile(i);
                            predefinePlayerController.character.takeDamage(1);
                            continue;
                        }
                    }
                    else {
                        if (bossController.character.projectiles.at(i).getGlobalBounds().intersects(playerController.character.sprite.getGlobalBounds())) {
                            bossController.character.eraseProjectile(i);
                            playerController.character.takeDamage(1);
                            continue;
                        }
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

                if(aiCheckBox.isChecked){
                    modelBoss.getActionReward(
                            bossEnv.getState(predefinePlayerController.character.sprite.getPosition()),
                            bossEnv.getReward(predefinePlayerController, bossController.character.sprite),
                            false);
                }
            }

            if(showStatesCases) {
                env.drawStateCases(&window, view);
            }
            if(showRewardsCases) {
                env.drawRewardCases(&window, view);
            }
        }
        else if(endLevel){
            window.clear(map.backgroundColor);
            endLevelView.draw(&window);
        }
        window.display();
    }
    return 0;
}
