#include "MapModel.hpp"
#include <iostream>
Colors::Colors() {
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
}

Colors::Colors(Json::Value root) {
    red = root["red"].asUInt();
    green = root["green"].asUInt();
    blue = root["blue"].asUInt();
    alpha = 0;
}

ObjectReference::ObjectReference(Json::Value root) {
    id = root["id"].asUInt();
    left = root["left"].asUInt();
    top = root["top"].asUInt();
    width = root["width"].asUInt();
    height = root["height"].asUInt();
    std::string buffType = root["type"].asString();
    if(buffType == "wall"){
        type = ObjectType::Wall;
    }
    else if(buffType == "platform"){
        type = ObjectType::Platform;
    }
    else if(buffType == "decor"){
        type = ObjectType::Decor;
    }
}

Ennemie::Ennemie() {

}

Ennemie::Ennemie(Json::Value root) {
    id = root["id"].asString();
    positionX = root["positionX"].asFloat();
    positionY = root["positionY"].asFloat();
}

Boss::BossPortal::BossPortal(Json::Value root) {
    path = root["path"].asString();
    positionX = root["positionX"].asFloat();
    positionY = root["positionY"].asFloat();
}

Boss::BossCharacter::BossCharacter(Json::Value root) {
    id = root["id"].asString();
    positionX = root["positionX"].asFloat();
    positionY = root["positionY"].asFloat();
}

Boss::Boss(Json::Value root) {
    character = BossCharacter(root["character"]);
    portal = BossPortal(root["portal"]);
}

Object::Object(Json::Value root) {
    id = root["id"].asUInt();
    scaleX = root["scaleX"].asFloat();
    scaleY = root["scaleY"].asFloat();
    positionX = root["positionX"].asFloat();
    positionY = root["positionY"].asFloat();
}

Reference::Reference(Json::Value root) {
    path = root["path"].asString();
    const Json::Value& objects1 = root["objects"];
    for (int j = 0; j < objects1.size(); j++) {
        objects.push_back(ObjectReference(objects1[j]));
    }
}

MapModel::MapModel(Json::Value root){
    const Json::Value& references1 = root["references"];
    const Json::Value& objects1 = root["objects"];
    const Json::Value& ennemies1 = root["ennemies"];
    for (int i = 0; i < references1.size(); i++){
        references.push_back(Reference(references1[i]));
    }
    for(int i = 0; i < objects1.size(); i++){
        objects.push_back(Object(objects1[i]));
    }
    for(int i = 0; i < ennemies1.size(); i++){
        ennemies.push_back(Ennemie(ennemies1[i]));
    }
    colors = Colors(root["colors"]);
    boss = Boss(root["boss"]);
}