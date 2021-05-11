#include "Map.h"
#include <dirent.h>
#include <fstream>
#include "../lib/json/json.h"
#include "../define.hpp"

using namespace std;
using namespace sf;
/**
 * Map génération
 */
Map::Map(std::string path){
    backgroundMoon = loadBackground(backgroundTextureMoon,430,0,90,90,950,15, false);
    backgroundMoon.setScale(2,2);
    backgroundCloud = loadBackground(backgroundTextureCloud,400,210,120,60,900,75, false);
    backgroundCloud.setScale(1.5,1.5);
    backgroundGround = loadBackground(backgroundTexutreGround,250,105,300,38,-60,118,true);
    backgroundGround2 = loadBackground(backgroundTexutreGround2,250,105,300,38,30,118,true);
    backgroundMoutain = loadBackground(backgroundTextureMoutain,250,175,180,38,430,545, false);
    backgroundMoutain.setScale(4,2);
    backgroundGround = loadBackground(backgroundTexutreGround,250,105,300,38,-60,600,true);
    backgroundGround2 = loadBackground(backgroundTexutreGround2,250,105,300,38,30,600,true);

    MapModel mapModel = loadAll(path);
    for(int i = 0; i < mapModel.objects.size(); i++){
        for(int j = 0; j < mapModel.references.size(); j++){
            for(int k = 0; k < mapModel.references[j].objects.size(); k++){
                ObjectReference objectReference = mapModel.references[j].objects[k];
                if(mapModel.objects[i].id == objectReference.id){
                    if(objectReference.type == ObjectType::Wall){
                        addWall(mapModel.objects[i].positionX, mapModel.objects[i].positionY,
                                objectReference.left, objectReference.top,
                                objectReference.width, objectReference.height);
                    }
                    else if(objectReference.type == ObjectType::Platform){
                        platform = loadBackground(texturePlatform, objectReference.left,
                                                  objectReference.top, objectReference.width,
                                                  objectReference.height, mapModel.objects[i].positionX,
                                                  mapModel.objects[i].positionY, false);
                        platform.setScale(1.2,1.2);
                    }
                }
            }
        }
    }


    //addWall(100, 560, 0, 0, 0, 0);
    //addWall(150,560);
    //addWall(150,510);
    //addWall(250,560);
}
/**
 * FUNCTION TO LOAD BACKGROUND
 * @param spriteTexture
 * @param rl
 * @param rt
 * @param rw
 * @param rh
 * @param x
 * @param y
 * @param repeat
 * @return
 */

MapModel Map::loadAll(std::string path) {
    Json::Value root;
    std::ifstream file;
    file.open(path);
    file >> root;
    file.close();
    return MapModel(root);
}

std::vector<std::string> Map::getAll(){
    DIR *dir;
    std::vector<std::string> result;
    struct dirent *ent;
    if ((dir = opendir(MAP_PATH)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            result.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
        perror ("");
    }
    return result;
}

Sprite Map::loadBackground( sf::Texture &spriteTexture,int rl, int rt , int  rw,  int rh, int x , int y,bool repeat){
    Sprite bg;
    if (!spriteTexture.loadFromFile("../assets/map/Dungeon_Ruins_Tileset/Dungeon Ruins Tileset Day.png",sf::IntRect(rl,rt,rw,rh)))
    {
        cout << "Erreur durant le chargement de la texture." << endl;
    }
    else {
        spriteTexture.setRepeated(repeat);
        bg.setTexture(spriteTexture);
        if(repeat){
            bg.setTextureRect({100,0,2000,30});
        }
        bg.setPosition(x, y);
    }
    return bg;
}

void Map::addWall(float x, float y, int left, int top, int width, int height){
    // TEST WALL POSITION
    /**
     * TODO: Preparer la génération aléatoire
     */
    walls.push_back(loadBackground(TextureBigWall, left, top, width, height, x, y, false));
}

void Map::drawBackground(RenderWindow &window)
{
    window.draw(backgroundMoutain);
    window.draw(backgroundMoon);
    window.draw(backgroundCloud);
    window.draw(backgroundGround);
    window.draw(backgroundGround2);
    for(int i = 0; i < walls.size(); i++) {
        window.draw(walls.at(i));
    }
    window.draw(platform);
}