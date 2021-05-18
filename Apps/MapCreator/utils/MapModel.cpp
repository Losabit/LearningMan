#include "MapModel.hpp"
#include <iostream>

ObjectReference::ObjectReference(Json::Value root) {
    id = root["id"].asUInt();
    left = root["left"].asUInt();
    top = root["top"].asUInt();
    width = root["width"].asUInt();
    height = root["height"].asUInt();
    type = root["type"].asString();
}

Object::Object(Json::Value root) {
    id = root["id"].asUInt();
    scaleX = root["scaleX"].asUInt();
    scaleY = root["scaleY"].asUInt();
    positionX = root["positionX"].asUInt();
    positionY = root["positionY"].asUInt();
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
    for (int i = 0; i < references1.size(); i++){
        references.push_back(Reference(references1[i]));
    }
    for(int i = 0; i < objects1.size(); i++){
        objects.push_back(Object(objects1[i]));
    }
}