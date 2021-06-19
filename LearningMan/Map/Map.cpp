#include "Map.h"
#include <dirent.h>
#include <fstream>
#include "../lib/json/json.h"
#include "../define.hpp"
#include "../characters/Shotgunner.hpp"
#include <Windows.h>

using namespace std;
using namespace sf;
/**
 * Map génération
 */

Map::Map(){
    backgroundColor = DEFAULT_COLOR;
}

Map::Map(std::string path){
    MapModel mapModel = loadAll(path);
    backgroundColor = sf::Color(mapModel.colors.red, mapModel.colors.green, mapModel.colors.blue, mapModel.colors.alpha);
    boss = mapModel.boss;
    ennemies = mapModel.ennemies;

    sf::Texture texture;
    if(!texture.loadFromFile("../assets/map/Dungeon_Ruins_Tileset/Dungeon Ruins Tileset Night.png", IntRect(250,105,300,38)))
    {
        cout << "Erreur durant le chargement de la texture." << endl;
    }
    textures.insert(std::pair<int,sf::Texture>(-1, texture));
    sf::Sprite obj = loadBackground(textures.find(-1)->second, true);
    obj.setPosition(-60,600);
    //spriteGround.setTextureRect({100,0,2000,30});
    decors.push_back(obj);

    obj.setPosition(30,600);
    //spriteGround2.setTextureRect({100,0,2000,30});
    decors.push_back(obj);


    for(int i = 0; i < mapModel.references.size(); i++){
        for(int k = 0; k < mapModel.references[i].objects.size(); k++) {
            ObjectReference objectReference = mapModel.references.at(i).objects.at(k);
            sf::Texture texture;
            if(!texture.loadFromFile(mapModel.references.at(i).path, sf::IntRect(objectReference.left, objectReference.top, objectReference.width, objectReference.height)))
            {
                cout << "Erreur durant le chargement de la texture." << endl;
            }
            textures.insert(std::pair<int,sf::Texture>(objectReference.id, texture));
        }
    }

    for(int i = 0; i < mapModel.objects.size(); i++){
        for(int j = 0; j < mapModel.references.size(); j++){
            for(int k = 0; k < mapModel.references[j].objects.size(); k++){
                ObjectReference objectReference = mapModel.references[j].objects[k];
                if(mapModel.objects[i].id == objectReference.id){
                    sf::Sprite obj = loadBackground(textures.find(objectReference.id)->second, false);
                    obj.setPosition(mapModel.objects[i].positionX, mapModel.objects[i].positionY);
                    obj.setScale(mapModel.objects[i].scaleX, mapModel.objects[i].scaleY);

                    if(objectReference.type == ObjectType::Wall){
                        walls.push_back(obj);
                    }
                    else if(objectReference.type == ObjectType::Platform){
                        platforms.push_back(obj);
                    }
                    else if(objectReference.type == ObjectType::Decor){
                        decors.push_back(obj);
                    }
                }
            }
        }
    }
}

MapModel Map::loadAll(std::string path) {
    Json::Value root;
    std::ifstream file;
    file.open(path);
    file >> root;
    file.close();
    return MapModel(root);
}

std::vector<std::string> Map::getAvailableMapNames(){
    DIR *dir;
    std::vector<std::string> result;
    string buffString;
    struct dirent *ent;
    if ((dir = opendir(MAP_PATH)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            buffString = ent->d_name;
            if(buffString.find(".json") != string::npos)
                result.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
        perror ("");
    }
    return result;
}

Sprite Map::loadBackground(sf::Texture &spriteTexture, bool repeat){
    Sprite bg;
    spriteTexture.setRepeated(repeat);
    bg.setTexture(spriteTexture);
    if(repeat){
        bg.setTextureRect({100,0,6000,30});
    }
    return bg;
}

void Map::drawBackground(RenderWindow &window)
{
    for(int i = 0; i < platforms.size(); i++) {
        window.draw(platforms.at(i));
    }

    for(int i = 0; i < walls.size(); i++) {
        window.draw(walls.at(i));
    }

    for(int i = 0; i < decors.size(); i++) {
        window.draw(decors.at(i));
    }
}