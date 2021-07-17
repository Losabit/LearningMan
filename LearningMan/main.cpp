#include <iostream>
#include <list>
#include <regex>
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
#include "utils/HitboxManager.hpp"
#include "utils/CollisionManager.hpp"
#include "utils/Portal.hpp"
#include "learningAlgorithms/QLearning.hpp"
#include "learningAlgorithms/Environment.h"

using namespace std;

//ToDo
int main() {
    bool onPlatform = false;
    bool SHOWHITBOX = false;
    sf::Clock hitboxClock = sf::Clock();
    sf::Clock pauseClock = sf::Clock();
    sf::Clock levelClock;
    bool endLevel = false;
    float pauseCooldown = 0.5f;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LearningMan");
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("../assets/others/logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture lifebar;
    lifebar.loadFromFile("../assets/GUI/lifebar.png", IntRect(52, 61, 50, 28));
    sf::Texture lifebarEmpty;
    lifebarEmpty.loadFromFile("../assets/GUI/lifebar.png", IntRect(190, 61, 50, 28));
    Sprite lifebarSprite;
    lifebarSprite.setTexture(lifebar);
    lifebarSprite.setPosition(BOSS_LIFEBAR_POSITION_X, 615);
    lifebarSprite.setScale(0.5,0.5);
    Sprite lifebarEmptySprite;
    lifebarEmptySprite.setTexture(lifebarEmpty);
    lifebarEmptySprite.setPosition(BOSS_LIFEBAR_POSITION_X, 615);
    lifebarEmptySprite.setScale(0.5,0.5);

    Container containerLifebar(lifebarSprite, 10, 25);
    containerLifebar.AddSecondarySprite(lifebarEmptySprite);

    sf::View view(sf::FloatRect(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT));
    sf::View initialView = window.getView();

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

    Texture textureHealth;
    textureHealth.loadFromFile(GUI_ASSETS_PATH "/health.png");
    Sprite spriteHealth(textureHealth, IntRect(0, 0, 901, 900));
    spriteHealth.setScale(0.02, 0.02);
    Container containerHealth(spriteHealth, 5, 25);

    UserConfiguration userConfiguration;

    Texture textureCheckBox;
    textureCheckBox.loadFromFile(GUI_ASSETS_PATH "/checkbox.png");
    bool checkBoxAI = false;
    sf::Clock checkboxClock = sf::Clock();
    Sprite checkBoxAIUnchecked(textureCheckBox, IntRect(15, 65, 75, 75));
    checkBoxAIUnchecked.move(1000, 0);
    Sprite checkBoxAIChecked(textureCheckBox, IntRect(112, 65, 75, 75));
    checkBoxAIChecked.move(1000, 0);
    Text textCheckBox;
    textCheckBox.setString("AI Mode");
    textCheckBox.setCharacterSize(24);
    textCheckBox.setFillColor(sf::Color::White);
    textCheckBox.move(900, 20);
    Font font;
    if(!font.loadFromFile("../ressources/policy/OrelegaOne-Regular.ttf")){
        std::cout << "font not find" << std::endl;
    }
    textCheckBox.setFont(font);

    EndLevelView endLevelView;

    Character heros = Heros();
    PlayerController playerController(&heros);
    playerController.character.sprite.setPosition(HEROS_INITIAL_POSITION);
    CollisionManager playerCollision(&playerController);

    PredefineController predefinePlayerController(&heros);
    QLearning model(0.1, 1.0, 0.9);
    Environment env(HEROS_INITIAL_POSITION);
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
    bool takePortal = false;
    //playerController.character.sprite.setPosition(4000, 475);
    int ennemiesCount = 0;

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
                if(checkBoxAI){
                    if(model.canPlay()) {
                        predefinePlayerCollision.checkCollisions();
                        PredefineAction action = model.getAction(
                                env.getState(predefinePlayerController.character.sprite.getPosition()),
                                env.getReward(predefinePlayerController.character.sprite.getPosition()));
                        model.debug(60.0);
                        if (predefinePlayerController.play(action) == Action::ToDestroy) {
                            startGame = false;
                            predefinePlayerController.character.reset(HEROS_INITIAL_POSITION);
                            window.setView(initialView);
                            for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                                //(*itEnnemies)->character.reset();
                            }
                        } else {
                            view.setCenter(predefinePlayerController.character.sprite.getPosition().x, 500);
                            window.setView(view);
                        }
                        model.getActionReward(env.getState(predefinePlayerController.character.sprite.getPosition()),
                                              env.getReward(predefinePlayerController.character.sprite.getPosition()),
                                              false);
                    }
                    else{
                        predefinePlayerController.play(PredefineAction::WaitAction);
                        view.setCenter(predefinePlayerController.character.sprite.getPosition().x, 500);
                        window.setView(view);
                    }
                }
                else {
                    playerCollision.checkCollisions();
                    if (playerController.play() == Action::ToDestroy) {
                        startGame = false;
                        playerController.character.reset(HEROS_INITIAL_POSITION);
                        window.setView(initialView);
                        for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                            //(*itEnnemies)->character.reset();
                        }
                    } else {
                        view.setCenter(playerController.character.sprite.getPosition().x, 500);
                        window.setView(view);
                    }
                }
                if(!takePortal) {
                    for(auto itEnnemiCollision = ennemiesCollisions.begin(); itEnnemiCollision != ennemiesCollisions.end(); itEnnemiCollision++){
                        itEnnemiCollision->checkCollisions();
                        /*
                        for(auto itEnnemi = ennemies.begin(); itEnnemi != ennemies.end(); itEnnemi++){
                            if(itEnnemiCollision->controller != (*itEnnemi))
                                itEnnemiCollision->checkCharacterCollisions((*itEnnemi)->character.sprite);
                        }
                         */
                    }
                    if(checkBoxAI){
                        if (predefinePlayerController.character.sprite.getGlobalBounds().intersects(
                                portal.getSprite().getGlobalBounds())) {
                            predefinePlayerController.character.sprite.setPosition(map.boss.character.positionX,
                                                                          map.boss.character.positionY);
                            takePortal = true;
                        }

                        for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                            (*itEnnemies)->setPlayerPosition(predefinePlayerController.character.sprite.getPosition());
                            (*itEnnemies)->play(predefinePlayerController.character);
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
                    Action actionBoss;
                    if(checkBoxAI)
                        actionBoss = bossController.play(predefinePlayerController.character);
                    else
                        actionBoss = bossController.play(playerController.character);

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
                userConfiguration.clickEvent(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)));
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

                        if(checkBoxAI){
                            predefinePlayerCollision.clear();
                            //playerCollision.addObject(bossController.character.sprite, ObjectType::Wall);
                            predefinePlayerCollision.addObject(map.walls, ObjectType::Wall);
                            predefinePlayerCollision.addObject(map.platforms, ObjectType::Platform);
                        }
                        else {
                            playerCollision.clear();
                            //playerCollision.addObject(bossController.character.sprite, ObjectType::Wall);
                            playerCollision.addObject(map.walls, ObjectType::Wall);
                            playerCollision.addObject(map.platforms, ObjectType::Platform);
                        }
                        ennemiesCount = ennemies.size();
                        startGame = true;
                        break;
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
               userConfiguration.keyEvent(event.text.unicode);
            }
        }

        if(endLevel){
            window.clear(map.backgroundColor);
            endLevelView.draw(&window);
        }
        else if(startGame) {
            window.clear(map.backgroundColor);
            if(checkBoxAI){
                if (takePortal) {
                    containerLifebar.draw(&window, predefinePlayerController.character.sprite.getPosition().x -
                                                   lifebarSprite.getPosition().x + BOSS_LIFEBAR_POSITION_X, 0);
                }
                containerHealth.number = predefinePlayerController.character.health;
                containerHealth.draw(&window, predefinePlayerController.character.sprite.getPosition().x - 200,
                                     WINDOW_HEIGHT - CAMERA_HEIGHT - 50);
            }
            else {
                if (takePortal) {
                    containerLifebar.draw(&window, playerController.character.sprite.getPosition().x -
                                                   lifebarSprite.getPosition().x + BOSS_LIFEBAR_POSITION_X, 0);
                }
                containerHealth.number = playerController.character.health;
                containerHealth.draw(&window, playerController.character.sprite.getPosition().x - 200,
                                     WINDOW_HEIGHT - CAMERA_HEIGHT - 50);
            }
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
                float x = checkBoxAI ? predefinePlayerController.character.sprite.getPosition().x - 200 : playerController.character.sprite.getPosition().x - 200;
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
            if(checkBoxAI)
                window.draw(predefinePlayerController.character.sprite);
            else
                window.draw(playerController.character.sprite);
            if(takePortal){
                int healthBefore = bossController.character.health;
                if(bossController.character.health > 0) {
                    if(checkBoxAI)
                        BulletManager::manageBullets(&predefinePlayerController, &bossController, map.walls, &window);
                    else
                        BulletManager::manageBullets(&playerController, &bossController, map.walls, &window);
                    if (healthBefore != bossController.character.health) {
                        containerLifebar.changeTextureOf(bossController.character.health, 1);
                    }
                }

                window.draw(bossController.character.sprite);
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
                if(checkBoxAI)
                    BulletManager::manageBullets(&predefinePlayerController, &ennemies, map.walls,&window);
                else
                    BulletManager::manageBullets(&playerController, &ennemies, map.walls,&window);

                for (itEnnemies = ennemies.begin(); itEnnemies != ennemies.end(); itEnnemies++) {
                    window.draw((*itEnnemies)->character.sprite);
                    if((*itEnnemies)->character.id != "healer"){
                        if(checkBoxAI)
                            BulletManager::manageBullets((*itEnnemies), &predefinePlayerController, map.walls, &window);
                        else
                            BulletManager::manageBullets((*itEnnemies), &playerController, map.walls, &window);
                    }else{
                        if((*itEnnemies)->character.launchHeal) {
                            Healer::heal((*itEnnemies), &ennemies);
                            (*itEnnemies)->character.launchHeal = false;
                        }
                    }
                }
                window.draw(portal.getSprite());
            }
        }
        else{
            window.clear(DEFAULT_COLOR);
            userConfiguration.draw(&window);
            if(!userConfiguration.isOpen) {
                for (auto buttonRef = buttonsMap.begin(); buttonRef != buttonsMap.end(); buttonRef++) {
                    (*buttonRef).draw(&window);
                }

                if (checkBoxAI) {
                    window.draw(checkBoxAIChecked);
                } else {
                    window.draw(checkBoxAIUnchecked);
                }
                window.draw(textCheckBox);
            }
        }
        window.display();
    }
    return 0;
}
