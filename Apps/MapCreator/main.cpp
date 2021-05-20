#include <iostream>
#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "utils/MapManager.hpp"
#include "utils/HitboxManager.h"
#include "define.hpp"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "MapCreator");
    Font font;
    int yLag = 50;
    if(!font.loadFromFile("../ressources/OrelegaOne-Regular.ttf")){
        cout << "font not find" << endl;
    }
    sf::View view = window.getView();
    view.move(0, yLag);
    bool showView = false;

    Texture textureGround;
    textureGround.loadFromFile("../assets/map/Dungeon_Ruins_Tileset/Dungeon Ruins Tileset Night.png", IntRect(250,105,300,38));
    textureGround.setRepeated(true);
    Sprite spriteGround(textureGround);
    spriteGround.setPosition(-60,600);
    spriteGround.setTextureRect({100,0,2000,30});

    Sprite spriteGround2(textureGround);
    spriteGround2.setPosition(30,600);
    spriteGround2.setTextureRect({100,0,2000,30});

    Texture textureHeros;
    textureHeros.loadFromFile("../assets/characters/player/charge.png", IntRect(14, 0, 30, 25));
    Sprite spriteHeros(textureHeros);
    spriteHeros.setPosition(0, 583);

    // Color
    int red = 122;
    int green = 160;
    int blue = 122;

    sf::Text textColor;
    textColor.setFont(font);
    textColor.setString("Color");
    textColor.setCharacterSize(24);
    textColor.setFillColor(sf::Color::White);
    textColor.move(50, 30);

    Button buttonColor("../assets/button/simple/1.png",
                  IntRect(50,140,400,200),
                  textColor);
    buttonColor.sprite.setScale(0.5,0.5);
    buttonColor.move(sf::Vector2f(50, 0 + yLag));


    Texture textureWhite;
    textureWhite.loadFromFile("../assets/fondblanc.png");
    Texture textureWhiteSelected;
    textureWhiteSelected.loadFromFile("../assets/selectedfondblanc.png");
    Texture textureGrey;
    textureGrey.loadFromFile("../assets/fondgris.png");

    Sprite spriteView(textureWhite, sf::IntRect(0, 0, 10000, CAMERA_HEIGHT));
    sf::Clock viewClock;

    sf::Text textColorRGB;
    textColorRGB.setFont(font);
    textColorRGB.move(50,120 + yLag);
    textColorRGB.setCharacterSize(15);
    textColorRGB.setFillColor(sf::Color::Black);

    Sprite spriteColorText(textureWhite, IntRect(0, 0, 901, 900));
    spriteColorText.move(50, 100 + yLag);
    spriteColorText.setScale(0.06, 0.06);

    Sprite spriteColorInput(textureWhite, IntRect(0, 0, 901, 900));
    spriteColorInput.move(110, 100 + yLag);
    spriteColorInput.setScale(0.15, 0.06);

    Container containerColorText(spriteColorText, 3, 55, false);
    containerColorText.addText(textColorRGB, {"red", "green", "blue"});
    Container containerColorInput(spriteColorInput, 3, 55, false);
    textColorRGB.move(100,0);
    containerColorInput.addText(textColorRGB, {std::to_string(red), std::to_string(green), std::to_string(blue)});

    sf::Text textApplyColor;
    textApplyColor.setFont(font);
    textApplyColor.setString("Apply");
    textApplyColor.setCharacterSize(12);
    textApplyColor.setFillColor(sf::Color::White);
    textApplyColor.move(50, 15);

    Button buttonApplyColor("../assets/button/simple/1.png",
                        IntRect(50,140,480,250),
                        textApplyColor);
    buttonApplyColor.sprite.setScale(0.4,0.25);
    buttonApplyColor.move(sf::Vector2f(70, 270 + yLag));

    bool containerColorIsPrinted = false;
    int choosenColor = -1;



    //Object
    sf::Text textObject;
    textObject.setFont(font);
    textObject.setString("Objects");
    textObject.setCharacterSize(24);
    textObject.setFillColor(sf::Color::White);
    textObject.move(50, 30);

    Button buttonObject("../assets/button/simple/1.png",
                       IntRect(50,140,480,200),
                        textObject);
    buttonObject.sprite.setScale(0.5,0.5);
    buttonObject.move(sf::Vector2f(300, 0 + yLag));

    MapManager mapManager(USED_MAP);
    bool containerObjectIsPrinted = false;
    int choosenObject = -1;
    std::vector<Sprite> mapSprites;
    std::vector<int> mapSpritesIds;
    int choosenMapSprite = -1;


    //Object Modifier
    Sprite containerObjectModifier(textureGrey);
    containerObjectModifier.setScale(0.15, 0.7);
    containerObjectModifier.move(600,100 + yLag);

    sf::Text textObjectModifierPosition;
    textObjectModifierPosition.setFont(font);
    textObjectModifierPosition.move(650,100 + yLag);
    textObjectModifierPosition.setCharacterSize(18);
    textObjectModifierPosition.setFillColor(sf::Color::White);
    textObjectModifierPosition.setString("Position");

    sf::Text textObjectModifierPositionX;
    textObjectModifierPositionX.setFont(font);
    textObjectModifierPositionX.move(600,150 + yLag);
    textObjectModifierPositionX.setCharacterSize(15);
    textObjectModifierPositionX.setFillColor(sf::Color::White);
    textObjectModifierPositionX.setString("x :");

    Sprite inputObjectModifierPositionX(textureWhite, IntRect(0, 0, 901, 900));
    inputObjectModifierPositionX.move(650, 150 + yLag);
    inputObjectModifierPositionX.setScale(0.13, 0.03);

    sf::Text textInputObjectModifierPositionX;
    textInputObjectModifierPositionX.setFont(font);
    textInputObjectModifierPositionX.move(650,150 + yLag);
    textInputObjectModifierPositionX.setCharacterSize(15);
    textInputObjectModifierPositionX.setFillColor(sf::Color::Black);

    sf::Text textObjectModifierPositionY;
    textObjectModifierPositionY.setFont(font);
    textObjectModifierPositionY.move(600,200 + yLag);
    textObjectModifierPositionY.setCharacterSize(15);
    textObjectModifierPositionY.setFillColor(sf::Color::White);
    textObjectModifierPositionY.setString("y :");

    Sprite inputObjectModifierPositionY(textureWhite, IntRect(0, 0, 901, 900));
    inputObjectModifierPositionY.move(650, 200 + yLag);
    inputObjectModifierPositionY.setScale(0.13, 0.03);

    sf::Text textInputObjectModifierPositionY;
    textInputObjectModifierPositionY.setFont(font);
    textInputObjectModifierPositionY.move(650,200 + yLag);
    textInputObjectModifierPositionY.setCharacterSize(15);
    textInputObjectModifierPositionY.setFillColor(sf::Color::Black);

    sf::Text textObjectModifierScale;
    textObjectModifierScale.setFont(font);
    textObjectModifierScale.move(660,300 + yLag);
    textObjectModifierScale.setCharacterSize(18);
    textObjectModifierScale.setFillColor(sf::Color::White);
    textObjectModifierScale.setString("Scale");

    sf::Text textObjectModifierScaleX;
    textObjectModifierScaleX.setFont(font);
    textObjectModifierScaleX.move(600,350 + yLag);
    textObjectModifierScaleX.setCharacterSize(15);
    textObjectModifierScaleX.setFillColor(sf::Color::White);
    textObjectModifierScaleX.setString("x :");

    Sprite inputObjectModifierScaleX(textureWhite, IntRect(0, 0, 901, 900));
    inputObjectModifierScaleX.move(650, 350 + yLag);
    inputObjectModifierScaleX.setScale(0.13, 0.03);

    sf::Text textInputObjectModifierScaleX;
    textInputObjectModifierScaleX.setFont(font);
    textInputObjectModifierScaleX.move(650,350 + yLag);
    textInputObjectModifierScaleX.setCharacterSize(15);
    textInputObjectModifierScaleX.setFillColor(sf::Color::Black);

    sf::Text textObjectModifierScaleY;
    textObjectModifierScaleY.setFont(font);
    textObjectModifierScaleY.move(600,400 + yLag);
    textObjectModifierScaleY.setCharacterSize(15);
    textObjectModifierScaleY.setFillColor(sf::Color::White);
    textObjectModifierScaleY.setString("y :");

    Sprite inputObjectModifierScaleY(textureWhite, IntRect(0, 0, 901, 900));
    inputObjectModifierScaleY.move(650, 400 + yLag);
    inputObjectModifierScaleY.setScale(0.13, 0.03);

    sf::Text textInputObjectModifierScaleY;
    textInputObjectModifierScaleY.setFont(font);
    textInputObjectModifierScaleY.move(650,400 + yLag);
    textInputObjectModifierScaleY.setCharacterSize(15);
    textInputObjectModifierScaleY.setFillColor(sf::Color::Black);

    sf::Text textApplyObjectModifier;
    textApplyObjectModifier.setFont(font);
    textApplyObjectModifier.setString("Apply");
    textApplyObjectModifier.setCharacterSize(12);
    textApplyObjectModifier.setFillColor(sf::Color::White);
    textApplyObjectModifier.move(50, 15);

    Button buttonApplyObjectModifier("../assets/button/simple/1.png",
                           IntRect(50,140,480,200),
                                     textApplyObjectModifier);
    buttonApplyObjectModifier.sprite.setScale(0.4,0.25);
    buttonApplyObjectModifier.move(sf::Vector2f(620, 500 + yLag));

    std::string choosenObjectModifier = "";

    //Save
    sf::Text textSave;
    textSave.setFont(font);
    textSave.setString("Save");
    textSave.setCharacterSize(24);
    textSave.setFillColor(sf::Color::White);
    textSave.move(50, 30);

    Button buttonSave("../assets/button/simple/1.png",
                        IntRect(50,140,480,200),
                        textSave);
    buttonSave.sprite.setScale(0.5,0.5);
    buttonSave.move(sf::Vector2f(550, 0 + yLag));

    sf::Text textApplySave;
    textApplySave.setFont(font);
    textApplySave.setString("Apply");
    textApplySave.setCharacterSize(12);
    textApplySave.setFillColor(sf::Color::White);
    textApplySave.move(50, 15);

    Button buttonApplySave("../assets/button/simple/1.png",
                            IntRect(50,140,480,480),
                           textApplySave);
    buttonApplySave.sprite.setScale(0.4,0.25);
    buttonApplySave.move(sf::Vector2f(300, 400 + yLag));

    Sprite spriteSaveInput(textureWhiteSelected, IntRect(0, 0, 901, 750));
    spriteSaveInput.move(280, 300 + yLag);
    spriteSaveInput.setScale(0.24, 0.06);

    sf::Text textSaveInput;
    textSaveInput.setFont(font);
    textSaveInput.move(290,300 + yLag);
    textSaveInput.setCharacterSize(15);
    textSaveInput.setFillColor(sf::Color::Black);


    bool containerSaveIsPrinted = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if(buttonColor.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))
                && !containerSaveIsPrinted && !containerObjectIsPrinted) {
                    containerColorIsPrinted = !containerColorIsPrinted;
                    choosenColor = -1;
                }

                if(containerColorIsPrinted) {
                    for(int i = 0; i < containerColorInput.sprites.size(); i++){
                        Sprite spriteColorInput = containerColorInput.sprites.at(i);
                        if(spriteColorInput.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                            choosenColor = i;
                            containerColorInput.sprites.at(i).setTexture(textureWhiteSelected);
                        }
                        else{
                            containerColorInput.sprites.at(i).setTexture(textureWhite);
                        }
                    }

                    if(buttonApplyColor.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))) {
                        red = stoi(containerColorInput.texts.at(0).getString().toAnsiString());
                        green = stoi(containerColorInput.texts.at(1).getString().toAnsiString());
                        blue = stoi(containerColorInput.texts.at(2).getString().toAnsiString());
                    }
                }

                if(buttonObject.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))
                   && !containerSaveIsPrinted && !containerColorIsPrinted){
                    containerObjectIsPrinted = !containerObjectIsPrinted;
                }

                if(containerObjectIsPrinted){
                    for(int i = 0; i < mapManager.sprites.size(); i++){
                        if(mapManager.sprites.at(i).getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                            containerObjectIsPrinted = false;
                            choosenObject = i;
                            break;
                        }
                    }
                }
                else{
                    if(choosenObject != -1){
                        Sprite sprite = mapManager.sprites.at(choosenObject);
                        sprite.setPosition(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)));
                        mapSprites.push_back(sprite);
                        mapSpritesIds.push_back(mapManager.mapReferences.objects.at(choosenObject).id);
                        choosenObject = -1;
                        choosenMapSprite = mapSprites.size() - 1;
                        textInputObjectModifierPositionX.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getPosition().x));
                        textInputObjectModifierPositionY.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getPosition().y));
                        textInputObjectModifierScaleX.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getScale().x));
                        textInputObjectModifierScaleY.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getScale().y));
                    }
                    else{
                        for(int i = 0; i < mapSprites.size(); i++){
                            if(mapSprites.at(i).getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                                choosenMapSprite = i;
                                textInputObjectModifierPositionX.setString(std::to_string((int)(mapSprites.at(choosenMapSprite).getPosition().x)));
                                textInputObjectModifierPositionY.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getPosition().y));
                                textInputObjectModifierScaleX.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getScale().x));
                                textInputObjectModifierScaleY.setString(std::to_string((int)mapSprites.at(choosenMapSprite).getScale().y));
                                break;
                            }
                        }
                    }
                }

                if(choosenMapSprite != -1){
                    if(buttonApplyObjectModifier.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        mapSprites.at(choosenMapSprite).setPosition(stof(textInputObjectModifierPositionX.getString().toAnsiString()), stof(textInputObjectModifierPositionY.getString().toAnsiString()));
                        mapSprites.at(choosenMapSprite).setScale(stof(textInputObjectModifierScaleX.getString().toAnsiString()), stof(textInputObjectModifierScaleY.getString().toAnsiString()));
                    }

                    if(inputObjectModifierPositionX.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        inputObjectModifierPositionX.setTexture(textureWhiteSelected);
                        inputObjectModifierPositionY.setTexture(textureWhite);
                        inputObjectModifierScaleX.setTexture(textureWhite);
                        inputObjectModifierScaleY.setTexture(textureWhite);
                        choosenObjectModifier = "position_x";
                    }
                    else if(inputObjectModifierPositionY.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        inputObjectModifierPositionY.setTexture(textureWhiteSelected);
                        inputObjectModifierPositionX.setTexture(textureWhite);
                        inputObjectModifierScaleX.setTexture(textureWhite);
                        inputObjectModifierScaleY.setTexture(textureWhite);
                        choosenObjectModifier = "position_y";
                    }
                    else if(inputObjectModifierScaleX.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        inputObjectModifierScaleX.setTexture(textureWhiteSelected);
                        inputObjectModifierPositionX.setTexture(textureWhite);
                        inputObjectModifierPositionY.setTexture(textureWhite);
                        inputObjectModifierScaleY.setTexture(textureWhite);
                        choosenObjectModifier = "scale_x";
                    }
                    else if(inputObjectModifierScaleY.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                        inputObjectModifierScaleY.setTexture(textureWhiteSelected);
                        inputObjectModifierPositionX.setTexture(textureWhite);
                        inputObjectModifierPositionY.setTexture(textureWhite);
                        inputObjectModifierScaleX.setTexture(textureWhite);
                        choosenObjectModifier = "scale_y";
                    }
                }
                else{
                    inputObjectModifierScaleY.setTexture(textureWhite);
                    inputObjectModifierPositionX.setTexture(textureWhite);
                    inputObjectModifierPositionY.setTexture(textureWhite);
                    inputObjectModifierScaleX.setTexture(textureWhite);
                    choosenObjectModifier = "";
                }

                if(buttonSave.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))
                   && !containerColorIsPrinted && !containerObjectIsPrinted){
                    containerSaveIsPrinted = !containerSaveIsPrinted;
                }

                if(containerSaveIsPrinted && buttonApplySave.sprite.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i (event.mouseButton.x, event.mouseButton.y)))){
                    mapManager.save("../out/" + textSaveInput.getString().toAnsiString() + ".json", mapSprites, mapSpritesIds, Vector3i(red, green, blue));
                    containerSaveIsPrinted = false;
                    textSaveInput.setString("");
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                choosenObject = -1;
                choosenMapSprite = -1;
            }

            if(!containerObjectIsPrinted && !containerSaveIsPrinted && !containerColorIsPrinted) {
                if (Keyboard::isKeyPressed(Keyboard::V) && viewClock.getElapsedTime().asSeconds() > 0.5) {
                    showView = !showView;
                    viewClock.restart();
                }

                float x = 0;
                float y = 0;
                if (Keyboard::isKeyPressed(Keyboard::Q)) {
                    x = -10.f;
                } else if (Keyboard::isKeyPressed(Keyboard::D)) {
                    x = 10.f;
                } else if (Keyboard::isKeyPressed(Keyboard::Z)) {
                    y = -10.f;
                } else if (Keyboard::isKeyPressed(Keyboard::S)) {
                    y = 10.f;
                }
                if(x != 0 || y != 0) {
                    if (choosenMapSprite == -1) {
                        view.move(x, y);
                        buttonColor.move(Vector2f(x, y));
                        containerColorInput.move(Vector2f(x, y));
                        containerColorText.move(Vector2f(x, y));
                        buttonApplyColor.move(Vector2f(x, y));

                        buttonObject.move(Vector2f(x, y));
                        containerObjectModifier.move(Vector2f(x, y));
                        textObjectModifierPosition.move(Vector2f(x, y));

                        textObjectModifierPositionX.move(Vector2f(x, y));
                        textInputObjectModifierPositionX.move(Vector2f(x, y));
                        inputObjectModifierPositionX.move(Vector2f(x, y));

                        textObjectModifierPositionY.move(Vector2f(x, y));
                        textInputObjectModifierPositionY.move(Vector2f(x, y));
                        inputObjectModifierPositionY.move(Vector2f(x, y));

                        textObjectModifierScale.move(Vector2f(x, y));
                        textObjectModifierScaleX.move(Vector2f(x, y));
                        textInputObjectModifierScaleX.move(Vector2f(x, y));
                        inputObjectModifierScaleX.move(Vector2f(x, y));

                        textObjectModifierScaleY.move(Vector2f(x, y));
                        textInputObjectModifierScaleY.move(Vector2f(x, y));
                        inputObjectModifierScaleY.move(Vector2f(x, y));
                        buttonApplyObjectModifier.move(Vector2f(x, y));

                        mapManager.move(Vector2f(x, y));

                        buttonSave.move(Vector2f(x, y));
                        buttonApplySave.move(Vector2f(x, y));
                        spriteSaveInput.move(Vector2f(x, y));
                        textSaveInput.move(Vector2f(x, y));
                    } else {
                        mapSprites.at(choosenMapSprite).move(Vector2f(x, y));
                        textInputObjectModifierPositionX.setString(
                                std::to_string((int) mapSprites.at(choosenMapSprite).getPosition().x));
                        textInputObjectModifierPositionY.setString(
                                std::to_string((int) mapSprites.at(choosenMapSprite).getPosition().y));
                        textInputObjectModifierScaleX.setString(
                                std::to_string((int) mapSprites.at(choosenMapSprite).getScale().x));
                        textInputObjectModifierScaleY.setString(
                                std::to_string((int) mapSprites.at(choosenMapSprite).getScale().y));
                    }
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if(!containerObjectIsPrinted && !containerSaveIsPrinted && !containerColorIsPrinted && choosenMapSprite != -1){
                    if (event.text.unicode == 8) {
                        mapSprites.erase(mapSprites.begin() + choosenMapSprite);
                        mapSpritesIds.erase(mapSpritesIds.begin() + choosenMapSprite);
                        choosenMapSprite = -1;
                    }
                }

                if(containerColorIsPrinted && choosenColor != -1) {
                    if (event.text.unicode == 8) {
                        containerColorInput.texts.at(choosenColor).setString(
                                containerColorInput.texts.at(choosenColor).getString().toAnsiString().substr(0, containerColorInput.texts.at(choosenColor).getString().toAnsiString().size() - 1));
                    } else if(containerColorInput.texts.at(choosenColor).getString().toAnsiString().size() < 3){
                        containerColorInput.texts.at(choosenColor).setString(
                                containerColorInput.texts.at(choosenColor).getString().toAnsiString() + static_cast<char>(event.text.unicode));
                    }
                }

                if(containerSaveIsPrinted){
                    if (event.text.unicode == 8) {
                        textSaveInput.setString(
                                textSaveInput.getString().toAnsiString().substr(0, textSaveInput.getString().toAnsiString().size() - 1));
                    } else {
                        textSaveInput.setString(
                                textSaveInput.getString().toAnsiString() + static_cast<char>(event.text.unicode));
                    }
                }

                if(choosenMapSprite != -1){
                    if (event.text.unicode == 8) {
                        if(choosenObjectModifier == "position_x"){
                            textInputObjectModifierPositionX.setString(
                                    textInputObjectModifierPositionX.getString().toAnsiString().substr(0, textInputObjectModifierPositionX.getString().toAnsiString().size() - 1));
                        }
                        else if(choosenObjectModifier == "position_y"){
                            textInputObjectModifierPositionY.setString(
                                    textInputObjectModifierPositionY.getString().toAnsiString().substr(0, textInputObjectModifierPositionY.getString().toAnsiString().size() - 1));
                        }
                        else if(choosenObjectModifier == "scale_x"){
                            textInputObjectModifierScaleX.setString(
                                    textInputObjectModifierScaleX.getString().toAnsiString().substr(0, textInputObjectModifierScaleX.getString().toAnsiString().size() - 1));
                        }
                        else if(choosenObjectModifier == "scale_y"){
                            textInputObjectModifierScaleY.setString(
                                    textInputObjectModifierScaleY.getString().toAnsiString().substr(0, textInputObjectModifierScaleY.getString().toAnsiString().size() - 1));
                        }
                    } else {
                        if(choosenObjectModifier == "position_x"){
                            textInputObjectModifierPositionX.setString(
                                    textInputObjectModifierPositionX.getString().toAnsiString() + static_cast<char>(event.text.unicode));
                        }
                        else if(choosenObjectModifier == "position_y"){
                            textInputObjectModifierPositionY.setString(
                                    textInputObjectModifierPositionY.getString().toAnsiString() + static_cast<char>(event.text.unicode));
                        }
                        else if(choosenObjectModifier == "scale_x"){
                            textInputObjectModifierScaleX.setString(
                                    textInputObjectModifierScaleX.getString().toAnsiString() + static_cast<char>(event.text.unicode));
                        }
                        else if(choosenObjectModifier == "scale_y"){
                            textInputObjectModifierScaleY.setString(
                                    textInputObjectModifierScaleY.getString().toAnsiString() + static_cast<char>(event.text.unicode));
                        }

                    }
                }
            }
        }

        window.clear(sf::Color(red,green,blue,0));

        if(showView){
            spriteView.setPosition(spriteHeros.getPosition().x - CAMERA_WIDTH / 2, spriteHeros.getPosition().y - CAMERA_HEIGHT + 70);
            window.draw(spriteView);
        }

        window.setView(view);
        buttonColor.draw(&window);
        buttonObject.draw(&window);
        buttonSave.draw(&window);
        window.draw(spriteHeros);
        window.draw(spriteGround);
        window.draw(spriteGround2);

        if(containerColorIsPrinted) {
            containerColorInput.draw(&window);
            containerColorText.draw(&window);
            buttonApplyColor.draw(&window);
        }

        if(containerObjectIsPrinted){
            mapManager.draw(window);
        }
        else{
            if(choosenMapSprite != -1){
                window.draw(containerObjectModifier);
                window.draw(textObjectModifierPosition);
                window.draw(textObjectModifierPositionX);
                window.draw(inputObjectModifierPositionX);
                window.draw(inputObjectModifierPositionY);
                window.draw(textObjectModifierPositionY);
                window.draw(textObjectModifierScale);
                window.draw(textObjectModifierScaleX);
                window.draw(textObjectModifierScaleY);
                window.draw(inputObjectModifierScaleX);
                window.draw(inputObjectModifierScaleY);
                window.draw(textInputObjectModifierPositionX);
                window.draw(textInputObjectModifierPositionY);
                window.draw(textInputObjectModifierScaleX);
                window.draw(textInputObjectModifierScaleY);
                buttonApplyObjectModifier.draw(&window);
                window.draw(HitboxManager::getHitboxSprite(mapSprites.at(choosenMapSprite).getGlobalBounds()));
            }
            for(int i = 0; i < mapSprites.size(); i++){
                window.draw(mapSprites.at(i));
            }
        }

        if(containerSaveIsPrinted){
            buttonApplySave.draw(&window);
            window.draw(spriteSaveInput);
            window.draw(textSaveInput);
        }
        window.display();
    }
    return 0;
}
