#ifndef LEARNINGMAN_MAPMODEL_HPP
#define LEARNINGMAN_MAPMODEL_HPP

#include "../lib/json/json.h"
#include "../utils/CollisionManager.hpp"

class ObjectReference {
public:
    ObjectReference(Json::Value root);
    int id;
    int top;
    int left;
    int width;
    int height;
    ObjectType type;
};

class Reference {
public:
    Reference(Json::Value root);
    std::string path;
    std::vector<ObjectReference> objects;
};

class Object{
public:
    Object(Json::Value root);
    int id;
    int scaleX;
    int scaleY;
    int positionX;
    int positionY;
};

class MapModel {
public:
    MapModel(Json::Value root);
    std::vector<Reference> references;
    std::vector<Object> objects;
};



#endif //LEARNINGMAN_MAPMODEL_HPP
