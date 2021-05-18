#include "MapManager.hpp"
#include <iostream>
#include <fstream>
#include "../lib/json/json.h"

ObjectCut::ObjectCut(Json::Value root) {
    id = root["id"].asUInt();
    left = root["left"].asUInt();
    top = root["top"].asUInt();
    width = root["width"].asUInt();
    height = root["height"].asUInt();
    type = root["type"].asString();
}

MapCut::MapCut() {

}

MapCut::MapCut(Json::Value root) {
    path = root["path"].asString();
    const Json::Value& objects1 = root["sprites"];
    for (int j = 0; j < objects1.size(); j++) {
        objects.push_back(ObjectCut(objects1[j]));
    }
}

MapManager::MapManager(std::string path) {
    mapReferences = loadAll(path);
    int leftLag = 100;
    int topLag = 200;
    for(int i = 0; i < mapReferences.objects.size(); i++){
        ObjectCut objectCut = mapReferences.objects.at(i);
        textures.push_back(sf::Texture());
        sprites.push_back(loadBackground(mapReferences.path, textures.at(i), objectCut.left, objectCut.top,
                                         objectCut.width, objectCut.height, false));
        sprites.at(i).move(objectCut.left + leftLag, objectCut.top + topLag);
    }
}

void MapManager::move(sf::Vector2f vector2F){
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i).move(vector2F);
    }
}

MapCut MapManager::loadAll(std::string path) {
    Json::Value root;
    std::ifstream file;
    file.open(path);
    file >> root;
    file.close();
    return MapCut(root);
}

void MapManager::save(std::string path, std::vector<sf::Sprite> objects,  std::vector<int> ids, sf::Vector3i colors) {
    std::ofstream outfile (path);
    Json::Value root;

    root["colors"] = Json::Value();
    root["colors"]["red"] = colors.x;
    root["colors"]["green"] = colors.y;
    root["colors"]["blue"] = colors.z;


    root["objects"] = Json::Value();
    for(int i = 0; i < objects.size(); i++){
        Json::Value jsonObject;
        jsonObject["id"] = ids.at(i);
        jsonObject["scaleX"] = objects.at(i).getScale().x;
        jsonObject["scaleY"] = objects.at(i).getScale().y;
        jsonObject["positionX"] = objects.at(i).getPosition().x;
        jsonObject["positionY"] = objects.at(i).getPosition().y;
        root["objects"].append(jsonObject);
    }

    root["references"] = Json::Value();
    Json::Value references;
    references["objects"] = Json::Value();
    for(int i = 0; i < mapReferences.objects.size(); i++){
        Json::Value object;
        object["id"] = mapReferences.objects.at(i).id;
        object["type"] = mapReferences.objects.at(i).type;
        object["left"] = mapReferences.objects.at(i).left;
        object["top"] = mapReferences.objects.at(i).top;
        object["width"] = mapReferences.objects.at(i).width;
        object["height"] = mapReferences.objects.at(i).height;
        references["objects"].append(object);
    }
    references["path"] = mapReferences.path;
    root["references"].append(references);

    outfile << root << std::endl;
    outfile.close();
}

sf::Sprite MapManager::loadBackground(std::string path, sf::Texture &spriteTexture, int rl, int rt , int rw, int rh, bool repeat){
    sf::Sprite bg;
    if (!spriteTexture.loadFromFile(path,sf::IntRect(rl,rt,rw,rh)))
    {
        std::cout << "Erreur durant le chargement de la texture." << std::endl;
    }
    else {
        spriteTexture.setRepeated(repeat);
        bg.setTexture(spriteTexture);
        if(repeat){
            bg.setTextureRect({100,0,2000,30});
        }
    }
    return bg;
}

void MapManager::draw(sf::RenderWindow &window){
    for(int i = 0; i < sprites.size(); i++){
        sprites.at(i).setTexture(textures.at(i));
        window.draw(sprites.at(i));
    }
}